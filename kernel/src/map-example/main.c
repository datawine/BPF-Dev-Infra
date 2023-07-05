#include "all.h"

struct {
	__uint(type, BPF_MAP_TYPE_ARRAY);
	__uint(max_entries, 3);
	__type(key, __u32);
	__type(value, __u64);
} arraymap SEC(".maps");

SEC("tracepoint/syscalls/sys_enter_execve")
int bpf_prog(void *ctx) {
  u64 cur_time = bpf_ktime_get_ns();

  bpf_printk("current time %lu\n", cur_time);

  u32 key = 0;
  u64 value = cur_time;
  bpf_map_update_elem(&arraymap, &key, &value, BPF_ANY);

  return 0;
}

char _license[] SEC("license") = "GPL";