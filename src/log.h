#ifndef _LOG_H
#define _LOG_H

#include <stdio.h>
#include <stdarg.h>

/* Singleton class for logging things with the correct verbosity level */

#define LOG_FILE "log"
#ifndef VERBOSITY
#  ifdef DEBUG_BUILD
#    define VERBOSITY DEBUG
#  else
#    define VERBOSITY WARNING
#  endif
#endif

enum VerbLevel{
    DEBUG, /* all messages are printed */
    WARNING, /* debug_asserts reached are warned about */
    FAILURE /* always on, says that something failed */
};

class logger {
    private:
        logger() { }
        VerbLevel verbosity;
        FILE* output = NULL;
    public:
        logger(logger const&) = delete;
        void operator=(logger const&) =delete;

        static logger& get(){
            static logger instance;
            return instance;
        }

        VerbLevel getVerbosity(){
            return verbosity;
        }
        void setVerbosity(VerbLevel v){
            verbosity = v;
        }

        void openFile(){
            output = fopen(LOG_FILE, "w");
        }
        void closeFile(){
            fclose(output);
        }

        void log(VerbLevel v, const char* fmt, ...){
            va_list ap;
            va_start(ap, fmt);
            if(v >= verbosity){
                if(v == DEBUG) fprintf(output,"DEBUG:\t");
                if(v == WARNING) fprintf(output,"WARNING:\t");
                if(v == FAILURE) fprintf(output,"FAILURE:\t");
                vfprintf(output, fmt, ap);
                fprintf(output, "\n");
            }
            va_end(ap);
        }
};

#define LOG(level, fmt, ...) (logger::get().log(level, fmt, __VA_ARGS__))

#endif /* _LOG_H */
