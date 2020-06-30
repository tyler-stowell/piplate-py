#include <Python.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include "../pi-plate-module/module/piplate.h"

static PyObject *plate_cmd(PyObject *self, PyObject *args){
	struct message m = BASE_MESSAGE;

	FILE *fp = fopen("/dev/PiPlates", "r");

	if(!fp)
		return NULL;

	if(!PyArg_ParseTuple(args, "iiiiip", &m.addr, &m.cmd, &m.p1, &m.p2, &m.bytesToReturn, &m.useACK))
		return NULL;

	ioctl(fileno(fp), PIPLATE_SENDCMD, &m);

	fclose(fp);

	//Extract and return m->rxBuf

	PyObject *l = PyList_New(0);
	int i;
	for(i = 0; i < m.bytesToReturn; i++){
		PyList_Append(l, Py_BuildValue("i", m.rBuf[i]));
	}

	return l;
}

static PyMethodDef PlateMethods[] = {
	{"sendCMD", plate_cmd, METH_VARARGS, "Send a command to a plate."},
	{NULL, NULL, 0, NULL}
};

static struct PyModuleDef PlateModule = {
	PyModuleDef_HEAD_INIT,
	"plateio",
	"C library for python to use ioctl commands",
	-1,
	PlateMethods
};

PyMODINIT_FUNC PyInit_plateio(void){
	return PyModule_Create(&PlateModule);
}
