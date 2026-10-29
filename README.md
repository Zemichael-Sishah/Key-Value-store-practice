# Simple Key-Value Store

## learning outcomes

In this assignment, we explore more complex topics, _viz.,_

- demonstrate ability to understand and use **complex system APIs** (`bsearch`, `qsort`, `realloc`, _etc._).
- practice using more complex aspects of `C` and such as **function pointers**, and **`void *`**.
- gain further exposure to **test harnesses** and get an increased understanding of how to properly test code.

## conceptual requirements

**Key-value stores** are a common piece of infrastructure that underlies most of the web. For example, a popular page at facebook makes over 500 key-value `get` operations (see the paper, "[Scaling Memcache at Facebook](https://www.usenix.org/conference/nsdi13/technical-sessions/presentation/nishtala)" by Nishtala et al. NSDI '13.) and almost any massive webpage uses key-value stores to service thousands if not millions of requests a second.

Though common key-value stores such as [memcached](https://memcached.org/) are over 10 thousand lines of code, in this assignment, we'll be investigating a simple implementation of the core operations.

Here is an example from [Redis](https://redis.io/nosql/key-value-databases/):

![An image showing an example of a Key-Value store with keys and phone numbers](key_value_redis_example.webp)
[Image Credit: Redis Website]



## coding instructions

You must implement your code in the following file:

- `kv.c` &rarr; see `kv.h` for the set of functions to be implemented. 

You **should not** modify `kv.h` -- the function prototypes represent the "language" for communication between the code using your store, and your store. Since we will provide our own test code, it is essential that you conform to this interface.

- your implementation should be in `kv.c`, and you can alter the code in there as you see fit (**note:** do not change the function signatures)
- you'll at least need to define the `kv` structure (and any other structures you'd like), and the required functions.

So you need to implement the following functions:

```C
struct kv *kv_create(void) ;
void kv_destroy(struct kv *store) ;
void *kv_get(struct kv *store, unsigned long key) ;
int kv_put(struct kv *store, unsigned long key, void *value, void **prev) ;
```

Your implementation *must*,

1. implement the key-value store as an array that you expand using `realloc`,
2. use `bsearch` to search through the array in O(log n), and
3. use `qsort` to sort the array when `kv_put` adds new key/value pairs.

## building/compiling/running your code

As before, the repository includes a `Makefile`. The provided code does not have a `main()` function. As before, look at the examples in the `tests/` folder on how to use the code. You must write **another** `C` file with **your own** `main()` function that **calls the functions** in `kv.h`. 

Then just run,

```
$> make all
```

This will systematically compile and build the `C` files (including your newly created file).

**Note:** the above `make` command also builds a `util` target -- pay attention to what happens there (and also what, if anything, gets added to your folder).

## **valgrind** and memory errors

[Valgrind](https://valgrind.org) is a programming tool for **memory debugging**, **memory leak detection** and profiling. We will be checking your implementation using valgrind to ensure that you have **freed all the memory that you have allocated**.

You can use the included script, `valgrind_test.sh` for this, as follows:

```
sh valgrind_test.sh <executable name>
```

where `<executable name>` is the binary that you have compiled.

Note that you have to manually look at the `valgrind` output to determine if there are any faults, _e.g.,_

```
valgrind --leak-check=yes ./tests/01_llist_create.bin
```

In this (and future) homeworks, **<span style="color:red;">Valgrind tests count towards your grade</span>**!

## testing harness

In this assignment we will use a further refinement of a testing "harness" from the previous assignments. We provide a _test library_ for this purpose. Look at:

- `kv_test.{c|h}` for the details about the library 
-  sample tests in the `tests/` folder on how to use the library.

Using this testing library, you send in a **set of "actions"** that must be carried out. When testing your code, you often want to make your tests as simple to create and add to as possible. Codifying the sequence of actions you want your tests to take in a data-structure makes it much easier to understand the sequence, easier to change the testing code and easier to update your tests.

You must test your code well. For this homework, we provide an example of what it looks like to do **strong testing** of your functionality.

You can run the tests with:

```
$> make test
```

You'll see all of the commands that are run for the test, and you can run them manually if you need (_e.g.,_ in `gdb`).

The tests run in two phases:

1. **functional tests** &rarr; test most aspects of the API.
2. **valgrind tests** &rarr; run the functional tests in `valgrind`.

Note that you have to manually look at the `valgrind` output to determine if there are any faults.

The tests evaluate an increasing amount of complexity, so you should focus on getting **early tests working** before moving on to more complex ones.

We have provided you with **six working tests** in the `tests/` folder. In addition, there is one test **you** need to implement:

|file| test to be implemented | "input" file |
|----|------------------------|--------------|
| `03_simple.c` | `put` and `get` actions in a specific sequence | `03_simple2.test.h` |
||

The input file, `03_simple2.test.h` will be replaced with other inputs during grading. In addition, all of the remaining tests will be replaced with modified versions for grading (but will test the same functionality). So check your code for all possible edge/error conditions.

**Note:** while you can use `printf()` to debug and validate your program, you **must remove** all of them before submission. There will be **negative points** for any leftover print statements (see rubric below).

## submission instructions

As with previous homeworks, submission happens in two steps:
1. `git` and
2. uploading to the `submission server`.

### 1. **git** process

You must submit the following via `git`:

1. `kv.c` &rarr; your implementation of the sorting code
2. `tests/03_simple2.c` &rarr; your implementation of the test case
3. any additional test cases you have created -- place them in the `tests` folder

**Note:** **DO NOT** modify/submit any other code/files.

Once you have checked everything in via git, _i.e.,_

```
$> git add
```

Add a commit message:

```
git commit -a -m "Commit message"
```

and then do,

```
$> git push
```

### 2. Submit server process

**Please follow the next instructions carefully:**

Run the following script from your homework directory:

```
$> sh utils/create_submission.sh
```

> Note: If this command does not work, try "bash utils/create_submission.sh"

Then, submit the file named `handin.tgz` to the **[submit server](https://submit.cs.seas.gwu.edu)**

**Note:** your assignment **won't be graded** unless you **EXACTLY** follow all of the above steps.

### important details

- **do not** modify any other code/file than the one from the aforementioned instructions
- you will likely need to put in effort to **understand the tests** because your implementation will likely trigger some errors --- all of the code is there, so dive in!
- **comment** and **indent** your code properly
- remember that you must enter `git push` and submit to the submit server for your code to be "submitted" -- make sure that you are on the `main`/`master` branch of your repo

[**+** Print outs can be useful for debugging, but they require that you understand the inner workings of the code. Your customers, and other developers don't have that understanding, so prints serve to simply confuse the output. For the class, they make the auto-grader uniformly determine your answer is wrong ;-(]

If you do not follow the instructions in a precise manner, then you will likely **lose major parts of your grade**!



## grading rubric

To grade your assignment, we'll use the following files:

- `kv.c` 
- `tests/03_simple2.c`

in our test harness.

We expect to only need to `#include <kv.h>` (and `03_simple2.test.h` for the test case) in our test files, and link with your aforementioned `.c` files.

in our test harness (we'll use slightly modified versions of the provided tests). We will also check the two additional test cases to be implemented.

|score | phase |
|------|-------|
| `0`  | code does **not compile/build** |
| `+15` | basic code (`kv.c`) compiles and builds but **does not run** |
| `+30`| `+5` for **each** of the public test cases (`6` test cases) |
| `+30`| `+5` passing the **valgrind** test (without errors) for **each** public test case (`6` test cases) |
| `+15` | for the test case to be implemented (`tests/03_simple2.c`) |
| `+10` | passing the **valgrind** test (without errors) for `tests/03_simple2.c` |
|||
|**`100`**| Total Score |
||

**Important Caveats**

1. **-50%** &rarr; if your implementation contains _extraneous_ print outs
2. **+15%** &rarr; if you submit by the _early deadline_
