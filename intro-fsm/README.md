# Introduction to Finite State Machines

### The "Wait-and-React" Mindset

In standard coding, we tell the MCU: *"Do this, then do that."* In a **State
Machine**, we tell the MCU: *"Be this, until something happens."*

- **The Flowchart (The Old Way):** Like a recipe. You follow steps 1 to 10. If
step 4 takes forever, the whole system stalls.
- **The Statechart (The FSM Way):** Like a **Security Guard**. He sits in a
chair (**State**). He stays there until he hears a noise (**Event**). He checks
if he has the key (**Guard**). If yes, he opens the door (**Action**) and moves
to a new room (**Transition**).

### The Four Pillars of a State

1. **Entry Action** 
2. **Activity**
3. **Event/Trigger**
4. **Exit Action** 

### The "Transition" Formula

Every time the system moves, it follows this universal logic:

* **Event:** "The 'Enter' key was pressed."
* **Condition (Guard):** "Is the password exactly 4 digits?"
* **Action:** "Unlock the solenoid."
* **New State:** "Access Granted."

### Example

- **[main.c](Src/main.c)**
- **[fsm.h](Inc/fsm.h)**
- **[fsm.c](Src/fsm.c)**