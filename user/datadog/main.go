package main

import (
	"bytes"
	_ "embed"
	"fmt"
	"os"

	"github.com/sirupsen/logrus"

	manager "github.com/DataDog/ebpf-manager"
)

//go:embed kernel/kernel.o
var Probe []byte

var m = &manager.Manager{
	Probes: []*manager.Probe{
		{
			ProbeIdentificationPair: manager.ProbeIdentificationPair{
				EBPFFuncName: "bpf_prog",
			},
		},
	},
}

func readTracePipe() {
	f, err := os.Open("/sys/kernel/debug/tracing/trace_pipe")
	if err != nil {
		logrus.Fatal(err)
	}

	buf := make([]byte, 4096)
	for {
		if _, err := f.Read(buf); err != nil {
			logrus.Fatal(err)
		}

		fmt.Printf("%s\n", buf)
	}
}

func main() {
	// Initialize the manager
	if err := m.Init(bytes.NewReader(Probe)); err != nil {
		logrus.Fatal(err)
	}

	// Start the manager
	if err := m.Start(); err != nil {
		logrus.Fatal(err)
	}

	logrus.Println("successfully started, head over to /sys/kernel/debug/tracing/trace_pipe")

	readTracePipe()

	// Close the manager
	if err := m.Stop(manager.CleanAll); err != nil {
		logrus.Fatal(err)
	}
}
