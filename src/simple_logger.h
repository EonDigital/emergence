/**
 * Copyright Carl Kelso, Oct 4, 2024.  All Rights Reserved.
 */

#ifndef SRC_SIMPLE_LOGGER_H_
#define SRC_SIMPLE_LOGGER_H_


#include <stdio.h>

#define SIMPLE_LOGGER_DEST stdout
#define SIMPLE_LOGGER_INFO_MSG "INFO> "
#define SIMPLE_LOGGER_ERROR_MSG "ERROR> "
#define SLPRE ""
#define SLSUF "\n"

#define LOG_INFO( fmt, ... ) fprintf( SIMPLE_LOGGER_DEST, SLPRE SIMPLE_LOGGER_INFO_MSG fmt SLSUF, ##__VA_ARGS__ )
#define LOG_ERROR( fmt, ... ) fprintf( SIMPLE_LOGGER_DEST, SLPRE SIMPLE_LOGGER_ERROR_MSG fmt SLSUF, ##__VA_ARGS__ )


#endif /* SRC_SIMPLE_LOGGER_H_ */
