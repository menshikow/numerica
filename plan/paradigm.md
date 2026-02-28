For **numerica**, the best fit is:

**procedural / functional core + data-oriented representation where it matters + minimal OO (mostly none).**

Numerical methods are easiest to read, test, and trust when they look like the textbook algorithm: pure functions with explicit inputs/outputs.

## Recommended style

### 1) Core algorithms: functional/procedural

Make solvers and integrators mostly **pure functions**:

* input: `f`, domain (`[a,b]`, etc.), `Options`
* output: `Result` (value + status + iterations + residual)
* no hidden state, no globals, no virtual interfaces

This keeps:

* correctness obvious
* tests simple
* behavior reproducible

Example shape:

```cpp
numerica::root_result<double> brent(F&& f, double a, double b, roots_options opt = {});
```

### 2) Data-oriented where you process arrays

For stats, filtering, polynomial evaluation, etc., be **data-oriented**:

* accept `std::span<const T>` (contiguous view)
* avoid deep object graphs
* operate in tight loops

Example:

```cpp
double variance(std::span<const double> x);
double poly_eval(std::span<const double> c, double x); // Horner
```

This gives good performance and a clean mental model.

### 3) Use “OO” only for small config/value types

OO is fine for **value types** (plain structs), not for polymorphism:

* `options` structs
* `result` structs
* maybe a `running_stats` accumulator type (stateful by design)

Example:

```cpp
struct running_stats {
  void add(double x);
  double mean() const;
  double variance() const;
};
```

That’s still not “OO architecture”; it’s just a stateful helper.

## What to avoid (early)

### Avoid class hierarchies / virtual dispatch

* `IRootSolver` interfaces
* base classes
* runtime polymorphism for algorithms

It adds:

* complexity
* overhead
* harder-to-follow control flow
* harder testing/mocking (ironically)

### Avoid “expression template” linear algebra design

Eigen-style expression templates are powerful but not aligned with “learn by implementing”. They also complicate error messages and debugging.

## A good rule of thumb

* If it’s an **algorithm** → make it a **function**
* If it’s **data you incrementally update** → make it a **small struct**
* If it’s **bulk numeric data** → accept **`std::span`** and process in loops

## A concrete architecture mapping

* `scalar.h`: free functions + constants
* `stats.h`: mostly free functions; optional `running_stats`
* `roots.h`: free functions returning `root_result<T>`
* `integrate.h`: free functions returning `integrate_result<T>`
* `detail/`: internal helpers (also functions + small structs)

## Practical benefits

* Easy to teach (code reads like pseudocode)
* Easy to test (deterministic, no hidden state)
* Easy to optimize later (tight loops, clear data flow)
* API stays small and composable

If you want one sentence to lock it in:
**“Functional API, data-oriented inputs (`span`), structs for options/results, no OO hierarchies.”**
