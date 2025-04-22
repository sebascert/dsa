Introduction
========================================

**DSA Library** offers a collection of common Data Structures & Algorithms in
C, along with multiple utilities.

Library Interface
-----------------

The interface for algorithms consists of declarations of Algorithm functions
prefixed by ``dsa_`` namespace.

The interface for data structures assumes that struct fields are never directly
accessed regardless of them being hidden or not, declarations are prefixed by
the data structure name.

Common types are found in ``include/types`` which have no namespace but are
intended to avoid collisions, declarations in ``include/utils`` have static
linkage, although users can include them for extra utilities, but they have no
namespace.

.. code-block:: c

   /* algorithm base interface */
   type dsa_algorithm(/*args...*/);

   /* data structure base interface */
   struct data_struct{
       /*fields...*/

       // if data_struct contains allocator
       const struct allocator *const alloc;
   };

   // null constant for data_struct
   // NULL constant for data_struct
   const struct data_struct NULL_DATA_STRUCT {nulled_fields...}

   // if data_struct contains allocator, default to stdlib_allocator
   struct data_struct data_struct_new(/*fields...*/);
   // if data_struct contains allocator, creates it with given allocator
   struct data_struct data_struct_new_with_alloc(/*fields...*/, const struct* allocator);
   void data_struct_free(struct data_struct*);

   bool data_struct_is_null(const struct data_struct*);

   type data_struct_function(struct data_struct*, /*args...*/);
