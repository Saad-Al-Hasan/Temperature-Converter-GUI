#ifndef trim_newline_h
#define trim_newline_h

/**
 * @struct StringTrimmer
 * @brief Manager structure for string trimming operations
 *
 * This structure provides functionality to trim newline characters from strings,
 * encapsulating both the target string and the trimming function.
 */
typedef struct {
    char *target_string;                    /**< Pointer to the string to be trimmed */
    void (*trim_newline)(char *str);        /**< Function pointer to trim newline characters */
} StringTrimmer;

extern StringTrimmer string_trimmer;

#endif
