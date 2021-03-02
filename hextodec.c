#include <stdio.h>
#define MSIZE 11		/* Longitud maxima de la cadena que almacena el numero hexadecimal */

int LeerCad(char cad[], int);
int hextodec(char cad[], int);

int main(void)
{
	char hexcad[MSIZE];		/* Arreglo para almacenar el numero hexadecimal */
	int lcad;				/* Longitud del numero hexadecimal (con sufijo o sin sufijo) */
	int ndec;				/* Numero decimal equivalente al numero hexadecimal ingresado */
	printf("El programa recibe un numero hexadecimal ingresado por el usuario y despues muestra la equivalencia del valor en decimal.\n"
		"El programa puede recibir un numero hexadecimal; este numero puede tener como maximo 8 digitos.\n"
		"El rango hexadecimal de un numero permitido es de 0X0 - 0xFFFFFFFF.\n"
		"Se permite al usuario agregar el sufijo \"0x/0X\" al inicio del numero hexadecimal.\n\n"
		"--Comienza el programa--\n"); 
	printf("Ingrese la cadena de digitos hexadecimales; puede agregar el sufijo 0x/0X al inicio del numero:");
	lcad = LeerCad(hexcad, MSIZE);
	ndec = hextodec(hexcad, lcad);
	if (ndec != -1)
		printf("\nEl numero hexadecimal %s tiene un valor decimal de: %d", hexcad, ndec);
	else if (lcad == 0)
		printf("\nNo se ingreso ningun numero hexadecimal.");
	else
		printf("\nEl numero hexadecimal %s no es valido.", hexcad);
	return 0;
}

/* LeerCad: Lee el numero hexadecimal ingresado por el usuario */
int LeerCad(char cad[], int msize)
{
	int c, i;
	
	i = 0;
	while ((c = getchar()) != '\n') 
		if (i < msize - 1)
			cad[i++] = c;
	cad[i] = '\0';
	return i;
}

int RevNum(char cad[], int);

/* hextocad: Convierte los digitos hexadecimales en cad[] en un numero decimal */
int hextodec(char cad[], int tam)
{
	int i;		/* Indice de posicion en el arreglo cad */
	int ndec;	/* Numero decimal resultante */
	
	ndec = 0;
	i = RevNum(cad, tam);	/* Se revisa el numero y se devuelve la posicion del primer digito */
	if (i == -1 || i == tam) /* En caso de que el indice este al final de la cadena o fuera de ella, se invalida el numero decimal */
		ndec = -1; 
	for (; ndec >= 0 && i < tam; ++i)
		if (cad[i] >= '0' && cad[i] <= '9')
			ndec = 16 * ndec + (cad[i] - '0');
		else if (cad[i] >= 'a' && cad[i] <= 'f')
			ndec = 16 * ndec + (10 + cad[i] - 'a');
		else if (cad[i] >= 'A' && cad[i] <= 'F')
			ndec = 16 * ndec + (10 + cad[i] - 'A');
		else
			ndec = -1;	/* El numero tiene un digito que no es hexadecimal */
	return ndec;
}

#define MDIG 8		/* Maximo numero de digitos hexadecimales en el arreglo cad[] */

/* RevNum: Esta funcion comprueba si el numero hexadecimal ingresado es valido. */
/*		   Cuando es valido se devuelve la posicion de inicio del numero hexadecimal en el arreglo. */
/*		   Si es invalido se devuelve -1. */
int RevNum(char cad[], int tam)
{
	int pos;
	
	/* Cuando se ingresan un total de 8 digitos, se verifica si el primer digito despues del sufijo es un numero entre 0-7 */
	if (cad[0] == '0' && (cad[1] == 'x' || cad[1] == 'X'))
		if (tam - 2 == MDIG && (cad[2] < '0' || cad[2] > '7'))
			pos = -1;
		else
			pos = 2;
	else if (tam > MDIG)	/* El numero sin sufijo tiene que ser menor o igual a 8 digitos, de lo contrario es invalido */
		pos = -1;
	/* Cuando se ingresan un total de 8 digitos, se verifica si el primer digito es un numero entre 0-7 */
	else if (tam == MDIG && (cad[0] < '0' || cad[0] > '7'))
		pos = -1;
	else
		pos = 0;
	return pos;
}