# Advanced System Software — HW3: Cooperative Scheduler on Bare-Metal RISC-V

> Part of the [Advanced System Software](https://github.com/avishkar7/advanced-system-software) portfolio.

## Assignment

Implement a minimal cooperative multitasking kernel on a bare-metal RISC-V
target running under QEMU. Three user processes run to completion under the
control of a trap-driven scheduler that is entered via `ecall`. Each process
voluntarily gives up the CPU with `yield_()` and signals completion with
`exit_()`; the scheduler tracks per-process state and resumes yielded
processes at the instruction following their yield point.

## Approach

- **Trap entry (`ecall`).** `main()` fires an `ecall` to drop into machine-mode
  trap handling. The scheduler reads the ecall id from register `t6` to decide
  what the calling process requested.
- **Process state machine.** Each process carries a state variable:
  `0 = ready`, `1 = terminated`, `2 = yielded`. On a `yield_()` (ecall id 2)
  the scheduler reads `mepc`, advances it past the `ecall`, and stores it as the
  resume address so the process continues where it left off. On `exit_()`
  (ecall id 1) the process is marked terminated.
- **Round-robin dispatch.** The scheduler cycles through the three processes,
  skipping terminated ones, and returns to the machine when all three are done.

## Layout

| Path | Contents |
|------|----------|
| `src/main.c` | Boot entry; initializes UART and scheduler, then `ecall`s in |
| `src/scheduler.c` | Trap-based scheduler and per-process state machine |
| `src/processes.c` | The three demo processes (`process1..3`) |
| `src/trap.c`, `src/trap_entry.s` | Machine-mode trap vector and dispatch |
| `src/uart.c`, `src/start.c`, `src/startup.s` | UART driver and startup code |
| `inc/` | Headers (`riscv.h`, `scheduler.h`, `stdlib_.h`, …) |
| `Makefile`, `link.ld`, `gdb_init` | Build and debug scaffolding |
| `docs/handout.pdf` | Original assignment handout |

## Build & run

Requires the RISC-V toolchain (`riscv64-unknown-elf-*`) and QEMU
(`qemu-system-riscv64`), as provided in the course lab environment.

```bash
make            # build kernel.elf / kernel.img
make run        # boot under QEMU
make debug      # boot with the GDB stub (see gdb_init)
```

Expected output shows each process running, yielding, resuming, and exiting,
ending with `All done.`
