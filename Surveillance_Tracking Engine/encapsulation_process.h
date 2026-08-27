#ifndef encapsulation_process_h
#define encapsulation_process_h
#include <stddef.h>

/**
 * @struct SecureInput
 * @brief Secure input handling structure for sensitive data entry
 *
 * This structure provides a secure mechanism for handling sensitive input data
 * by encapsulating a buffer, its size, and a function pointer for hidden input
 * operations (such as password entry without echoing to the terminal).
 */
typedef struct {
    char buffer[256];                                           /**< Input buffer for storing secure data */
    size_t buffer_size;                                         /**< Size of the input buffer */
    void (*get_hidden_input)(char *buffer, size_t size);       /**< Function pointer for secure input operations */
} SecureInput;

extern SecureInput secure_input;

#endif
