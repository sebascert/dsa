# Data Structures & Algorithms in C (DSA)

This is the repository for the **DSA library**. The library is a collection
of common Data Structures and Algorithms implemented in C, along with multiple
utilities.

# Usage

Import the code into your project or build a library with the dsa's you need.

## Declaration Interface Format

The interface for algorithms consists of declarations of Algorithm functions
prefixed by `dsa_` namespace.

The interface for data structures assumes that struct fields are never directly
accessed regardless of them being hidden or not, declarations are prefixed by
the data structure name.

Common types are found in `include/types` which have no namespace but are
intended to avoid collisions, declarations in `include/utils` are internally
used, although users can include them for extra utilities, but they have no
namespace.

```c
/*algorithm base interface*/
type dsa_algorithm(/*args...*/);

/*data structure base interface*/
struct data_struct{
    //fields
};

// null constant for data_struct
// treated as a NULL pointer by data_struct_function
const struct data_struct NULL_DATA_STRUCT {nulled_fields...}

//default to stdlib_allocator
struct data_struct data_struct_new(/*fields...*/);
struct data_struct data_struct_new_with_allocator(/*fields...*/, const struct* allocator);
void data_struct_free(struct data_struct*);

type data_struct_function(struct data_struct*, /*args...*/);
```

## Testing

The project uses [criterion](https://github.com/Snaipe/Criterion) testing
framework, check their corresponding installation. Each dsa declaration
`include/category/dsa` is accompanied by a corresponding set of unit tests
located in `tests/category/dsa` directory.

compile and run:
```bash
# compile tests
make tests

# run the tests, check criterion docs for testing options
make tests ARGS='<args>'
# or
./build/test_dsa <args>
```

## Contributing

Contributions are welcome! If you'd like to contribute to this repository,
please fork the repository and submit a pull request with your changes. Be sure
to follow the coding standards and formatting in `.clang-format`.

## License

DSA source code is available under the MIT License.
