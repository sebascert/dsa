# C Data Structures and Algorithms

DSA is a collection of common Data Structures and Algorithms implemented in
C. [DSA_LIST.md](DSA_LIST.md) contains all the data structures and algorithms
and corresponding dependencies.

# Usage

Import the code into your project or build a library with the dsa's you need,
see [DSA_LIST.md](DSA_LIST.md) for the dependencies between dsa's.

## Declaration Interface Format

Declarations of Algorithm functions are consistently prefixed by `dsa_`
namespace, declarations related to Data Structures are prefixed by their name.
common types are found in `src/types` which have no namespace but are intended
to avoid collisions. Declarations in `src/utils` are internally used, although
users can include them for extra utilities, but they have no namespace.

```c
/*algorithm base interface*/
type dsa_algorithm(/*args...*/);

/*data structure base interface*/
typedef struct data_struct;

// null constant for data_struct
// treated as a NULL pointer by data_struct_function
#define null_data_struct {nulled_fields...}

data_struct data_struct_new(/*fields...*/);
void data_struct_free(data_struct* data_struct);

type data_struct_function(data_struct* data_struct, /*args...*/);
```

## Testing

The project uses [criterion](https://github.com/Snaipe/Criterion) testing
framework, check their corresponding installation. Each dsa in the `src`
directory is accompanied by a corresponding set of unit tests located in the
`tests` directory.

compile and run:
```bash
# compile tests
make tests

# run the tests, check criterion docs for testing options
make tests ARGS='<args>'
# or
./build/test_dsa <args>
```

## Cleaning after Compiling

```bash
# remove all object files
make clean

# also remove build/
make clean-all
```

## Contributing

Contributions are welcome! If you'd like to contribute to this repository,
please fork the repository and submit a pull request with your changes. Be sure
to follow the coding standards and formatting in `.clang-format`.

## License

c-dsa source code is available under the MIT License.
