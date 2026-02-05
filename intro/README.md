# Introduction

An **Embedded System** is a computerized system dedicated to a specific set of
real-world functions. Unlike general-purpose computers, these are integrated
directly with hardware to perform fixed tasks.

- **Real-Time Systems:** Systems where "correctness" depends on **timeliness**.
- **Hard Real-Time:** Missing a deadline is a total system failure.
- **Soft Real-Time:** Performance is measured by average throughput or response
time; occasional delays are acceptable.

### Design Constraints

Embedded development is driven by **Recurring Cost** (the cost to manufacture
each unit). This forces developers to optimize for:

- **Resources:** Minimal memory (RAM/Flash), low power consumption, and limited CPU cycles.
- **Performance/Throughput:** Transactions processed per unit of time.
- **Responsiveness:** Worst-case execution time (WCET).
- **Predictability:** Consistent timing across executions.
- **Safety/Reliability:** Implementation of Power-On Self-Tests (POST) and Built-In Tests (BIT).

### The Execution Environment

There are three primary ways to manage code execution on an MCU:

1. **Bareback (Bare Metal):** No OS. The application handles interrupts and
hardware directly. Best for extremely resource-constrained systems.

2. **RTOS (Real-Time Operating System):** Provides multitasking and scheduling.
Focuses on **predictability** rather than maximum speed.

- Uses **Event-driven** (priority-based) or **Time-based** (round-robin) scheduling.


3. **Middleware:** Standardized software layers (like CORBA or DDS) that connect
components, typically used in complex, distributed systems.

### The Embedded Toolchain

Development happens on a **Host** for a **Target**.

- **Cross-Compiler:** Generates machine code for the ARM Cortex-M4 architecture while running on x86 hardware.
- **Linker:** Combines object files and assigns them to specific memory addresses (Flash/RAM).
- **Debugger:** Utilizes JTAG or SWD protocols to step through code and inspect registers in real-time.

---

#  Object-Oriented Programming in C

While C is a structured language, it can implement Object-Oriented (OO) patterns
to improve code maintainability for MCUs.

### 1. Classes and Objects

- **Class:** Represented by a `struct` (attributes) and a set of functions
(operations) in a `.c`/`.h` pair.
- **Encapsulation:** The `.h` file exposes the public interface, while the `.c`
file hides private implementation details.
- **The `me` pointer:** Functions receive a pointer to the struct instance to
identify which "object" they are modifying.

### 2. Polymorphism and Inheritance

- **Polymorphism:** Using **function pointers** inside a struct. This allows the
same function call to execute different code depending on the specific hardware
or context.
- **Subclassing:** A "derived" struct contains a "base" struct as its first member. This allows the child to inherit the parent's data and specialized behavior.

This final section focuses on **Object-Oriented (OO) patterns** in C, specifically how to handle **Inheritance** and **Polymorphism** (virtual functions) when you are working on a constrained device like your STM32.

#### Specialization (Overriding Behavior)

In C, "Virtual Functions" are created using **Function Pointers** inside a struct.

- **The Goal:** Allow a "Child" version of a component to behave differently
than the "Parent" version without changing the parent's code.
- **The Mechanism:** Instead of calling a function directly, the code calls a
 pointer. To change the behavior, you simply point that pointer to a new,
 specialized function.

#### Extension (Adding Features)

To "inherit" from a base class in C, you use a technique called **Struct Embedding**.

- **The Rule:** You place the "Base" struct as the **very first member** of the
"Child" struct.
- **Why?** Because in C, a pointer to the start of the Child struct is also a
pointer to the start of the Base struct. This allows you to pass a `CachedQueue`
pointer into a function that expects a `Queue` pointer.

## Examples

- [main.c](Src/main.c)
- [sensor.h](Inc/sensor.h)
- [sensor.c](Src/sensor.c)
- [queue.h](Inc/queue.h)
- [queue.c](Src/queue.c)
