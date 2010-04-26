/*
 * sftphandle.c
 *
 * Copyright (C) Keyphrene.com 2005, All rights reserved
 *
 */
#include <Python.h>
#define SSH2_MODULE
#include "ssh2.h"

/*
 * ADD_METHOD(name) expands to a correct PyMethodDef declaration
 *   {  'name', (PyCFunction)SSH2_SFTP_handle_name, METH_VARARGS }
 * for convenience
 */
#define ADD_METHOD(name) { #name, (PyCFunction)SSH2_SFTP_handle_##name, METH_VARARGS, SSH2_SFTP_handle_##name##_doc }
static PyMethodDef SSH2_SFTP_handle_methods[] =
{
    { NULL, NULL }
};
#undef ADD_METHOD


/*
 * Constructor for SFTP_handle objects, never called by Python code directly
 *
 * Arguments: cert    - A "real" SFTP_handle certificate object
 *            dealloc - Boolean value to specify whether the destructor should
 *                      free the "real" SFTP_handle object
 * Returns:   The newly created SFTP_handle object
 */
SSH2_SFTP_handleObj *
SSH2_SFTP_handle_New(LIBSSH2_SFTP_HANDLE *sftphandle, int dealloc)
{
    SSH2_SFTP_handleObj *self;

    self = PyObject_New(SSH2_SFTP_handleObj, &SSH2_SFTP_handle_Type);

    if (self == NULL)
        return NULL;

    self->sftphandle = sftphandle;
    self->dealloc = dealloc;

    return self;
}

/*
 * Deallocate the memory used by the SFTP_handle object
 *
 * Arguments: self - The SFTP_handle object
 * Returns:   None
 */
static void
SSH2_SFTP_handle_dealloc(SSH2_SFTP_handleObj *self)
{
    //~ if (self->dealloc)
		//~ free(self->sftphandle);

    PyObject_Del(self);
}

/*
 * Find handleibute
 *
 * Arguments: self - The SFTP_handle object
 *            name - The handleibute name
 * Returns:   A Python object for the handleibute, or NULL if something went
 *            wrong
 */
static PyObject *
SSH2_SFTP_handle_getattr(SSH2_SFTP_handleObj *self, char *name)
{
    return Py_FindMethod(SSH2_SFTP_handle_methods, (PyObject *)self, name);
}

PyTypeObject SSH2_SFTP_handle_Type = {
    PyObject_HEAD_INIT(NULL)
    0,
    "SFTP_handle",
    sizeof(SSH2_SFTP_handleObj),
    0,
    (destructor)SSH2_SFTP_handle_dealloc,
    NULL, /* print */
    (getattrfunc)SSH2_SFTP_handle_getattr,
	NULL, /* sethandle */
    NULL, /* compare */
    NULL, /* repr */
    NULL, /* as_number */
    NULL, /* as_sequence */
    NULL, /* as_mapping */
    NULL, /* hash */
};

/*
 * Initialize the SFTP_handle
 *
 * Arguments: dict - The SSH2 module dictionary
 * Returns:   None
 */
int
init_SSH2_SFTP_handle(PyObject *dict)
{
    SSH2_SFTP_handle_Type.ob_type = &PyType_Type;
    Py_INCREF(&SSH2_SFTP_handle_Type);
    PyDict_SetItemString(dict, "SFTP_handleType", (PyObject *)&SSH2_SFTP_handle_Type);
    return 1;
}

