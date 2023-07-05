#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/resource.h>
#include <bpf/libbpf.h>


#define DEBUGFS "/sys/kernel/debug/tracing/"


void read_trace_pipe(void) {
	int trace_fd;

	trace_fd = open(DEBUGFS "trace_pipe", O_RDONLY, 0);
	if (trace_fd < 0)
		return;

	while (1) {
		static char buf[4096];
		ssize_t sz;

		sz = read(trace_fd, buf, sizeof(buf) - 1);
		if (sz > 0) {
			buf[sz] = 0;
			puts(buf);
		}
	}
}


struct bpf_object* load_bpf_file_object(char *path) {
    struct bpf_object* obj;
    obj = bpf_object__open(path);
    if (libbpf_get_error(obj)) {
        printf("ERROR: failed to open prog: '%s'\n", strerror(errno));
        return NULL;
    }

    if (bpf_object__load(obj)) {
        printf("ERROR: failed to load prog: '%s'\n", strerror(errno));
        return NULL;
    }
    return obj;
}


struct bpf_link* attach_prog_and_get_link(struct bpf_object* obj, const char* prog_name){
    struct bpf_program *prog;
    struct bpf_link *link;
    prog = bpf_object__find_program_by_name(obj, prog_name);
    if (prog == NULL) {
        printf("ERROR: no name: '%s'\n",prog_name);
        return NULL;
    }

    link = bpf_program__attach(prog);
    if (libbpf_get_error(link)) {
        printf("ERROR: failed to attach prog: '%s'\n", strerror(errno));
        return NULL;
    }
    return link;
}


int find_map_and_get_value(struct bpf_object* obj, const char* map_name, void* key, size_t key_size, 
                            void* value, size_t value_size, unsigned long long flag){
    struct bpf_map* map;
    map = bpf_object__find_map_by_name(obj,map_name);
    if (map==NULL){
        printf("ERROR: failed to get map: '%s'\n","arraymap");
        return 1;
    }
    if (bpf_map__lookup_elem(map,key,key_size,value,value_size,flag)){
        printf("ERROR: failed to get value\n");
        return 2;
    }
    return 0;
}


int load_bpf_file(char *path, char * prog_name) {
    struct bpf_object *obj;
    struct bpf_program *prog;
    struct bpf_link *link;
    obj = bpf_object__open(path);
    if (libbpf_get_error(obj)) {
        printf("ERROR: failed to open prog: '%s'\n", strerror(errno));
        return 1;
    }

    if (bpf_object__load(obj)) {
        printf("ERROR: failed to load prog: '%s'\n", strerror(errno));
        return 2;
    }

    prog = bpf_object__find_program_by_name(obj, prog_name);
    if (prog == NULL) {
        printf("ERROR: no name: '%s'\n",prog_name);
        return 3;
    }

    link = bpf_program__attach(prog);
    if (libbpf_get_error(link)) {
        printf("ERROR: failed to attach prog: '%s'\n", strerror(errno));
        return 4;
    }
    return 0;
}


int destroy_link_and_close_obj(struct bpf_object *obj,struct bpf_link *link) {
    bpf_link__destroy(link);
    bpf_object__close(obj);
    return 0;
}


int main(int argc, char **argv) {
    assert(argc == 3);

    int num;
    if ((num = load_bpf_file(argv[1], argv[2])) != 0) {
        printf("The error num is: %d.\n", num);
        printf("The kernel didn't load the BPF program\n");

        return -1;
    } 

    read_trace_pipe();

    return 0;
}