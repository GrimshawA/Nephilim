#include <stdlib.h>
#include <stdio.h>
#include <cassert>
#include <GL/glew.h>

#include "Program.h"
 
char *textFileRead(char *fn) {
    FILE *fp;
    char *content = NULL;
    int count = 0;
    if (fn != NULL) {
        fp = fopen(fn, "rt");
        if (fp != NULL) {
            fseek(fp, 0, SEEK_END);
            count = ftell(fp);
            rewind(fp);
            if (count > 0) {
                content = (char*) malloc(sizeof(char) * (count + 1));
                count = fread(content, sizeof(char), count, fp);
                content[count] = '\0';
            }
            fclose(fp);
        } else {
            printf("could not open \"%s\"\n", fn);
            exit(1);
        }
    }
    return content;
}

void printShaderLog(GLuint shader) {
    GLint  i;
    char* s;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &i);
    if (i > 0) {
        s = (GLchar*) malloc(i);
        glGetShaderInfoLog(shader, i, &i, s);
        fprintf(stderr, "compile log = '%s'\n", s);
    }
}

void checkShader(GLuint s) {
    GLint compiled;
    glGetShaderiv(s, GL_COMPILE_STATUS, &compiled);
    if (!compiled) {
        printShaderLog(s);
        exit(-1);
    }
}

int checkProgram(GLuint p) {
    GLint linked;
    glGetProgramiv(p, GL_LINK_STATUS, &linked);
    return linked;
}

Program::Program(int files, char** fileNames, char *options) {
    program = -1;
    vertexShader = -1;
    fragmentShader = -1;

    const char **contents = (const char**) malloc((files + 2) * sizeof(char*));

    int i;
    for (i = 0; i < files; ++i) {
        contents[i + 2] = textFileRead(fileNames[i]);
    }

    printf("LOADING %s\n", fileNames[files - 1]);

    if (program == -1) {
        program = glCreateProgram();
        vertexShader = glCreateShader(GL_VERTEX_SHADER);
        fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glAttachShader(program, vertexShader);
        glAttachShader(program, fragmentShader);
        assert(glGetError() == 0);
    }

    contents[0] = "#define _VERTEX_\n";
    contents[1] = options == NULL ? "" : options;
    glShaderSource(vertexShader, files + 2, contents, NULL);
    glCompileShader(vertexShader);
    checkShader(vertexShader);
    assert(glGetError() == 0);

    contents[0] = "#define _FRAGMENT_\n";
    glShaderSource(fragmentShader, files + 2, contents, NULL);
    glCompileShader(fragmentShader);
    checkShader(fragmentShader);
    assert(glGetError() == 0);

    for (i = 0; i < files; ++i) {
        free((void*) contents[i + 2]);
    }

    glBindAttribLocation(program, 1, "normal");
    glBindAttribLocation(program, 2, "color");

    glLinkProgram(program);
    GLint logLength;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);
    if (logLength > 0) {
        char *log = new char[logLength];
        glGetProgramInfoLog(program, logLength, &logLength, log);
        printf("%s", log);
    }

    if (checkProgram(program)) {
        assert(glGetError() == 0);
    } else {
        printShaderLog(vertexShader);
        printShaderLog(fragmentShader);
        exit(-1);
    }
}

Program::~Program() {
    glDeleteProgram(program);
    if (vertexShader != -1) {
        glDeleteShader(vertexShader);
    }
    if (fragmentShader != -1) {
        glDeleteShader(fragmentShader);
    }
}
