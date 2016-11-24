#ifndef BUILD_SETTINGS_H
#define BUILD_SETTINGS_H

// This file could be done through command line defines, but is being done here so that the defines can be documented.

/// <summary>
/// Defining this will cause the appropriate framework function (e.g. not ones in public_inc, but the ones in private_inc) to validate arguments passed to it.  Exceptions will be thrown if validation
/// fails.
/// </summary>
#define VALIDATE_FUNCTION_ARGUMENTS 1
// #undef VALIDATE_FUNCTION_ARGUMENTS

#endif /* BUILD_SETTINGS_H */