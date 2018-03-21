#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int MIL = 1000; 

struct dogType{
  char nombre [32];
  char tipo [32];
  int edad;
  char raza [16];
  int estatura;
  float peso;
  char genero;
  int next;
  
};


int hash(void * ap){
  char * c;
  c = ap; 
  int tmp = 0;
  for( int i = 0; i < sizeof(ap) ; i++){
    if( c[i] >= 97 )  tmp += c[i] - 32; 
    else tmp += c[i];
  }
  return (tmp % MIL) * sizeof(struct dogType); 
}



void ingresar_registro(void * ap, FILE *f){
 
  struct dogType * animal;
  int hashkey, numread, hashi;
  
  animal = ap;
  hashkey = hash(animal -> nombre);

  struct dogType * tmp;
  tmp = malloc(sizeof(struct dogType));
  
  hashi = hashkey;
  fseek(f,hashi, SEEK_SET);

  while( numread = fread(tmp, sizeof(struct dogType), 1, f) == 1 )
    {
   
      if(tmp -> next  == -1 )
	break;
      hashi = tmp -> next; 
      fseek(f,hashi, SEEK_SET);
    }
    
  if( numread == 1 ){
    printf("%i \n", hashi);
    fseek(f,0L, SEEK_END);  // busca el proximo espacio libre
    int pos = ftell(f);
    tmp -> next = pos;  // le asigna el valor de la pos del byte  a next
    fwrite(animal, sizeof(struct dogType), 1, f);
    
    fseek(f, hashi ,SEEK_SET); // vuelve a la pos del padre
    fwrite(tmp, sizeof(struct dogType), 1, f);
    
  }else {
    printf("entra no");
    fseek(f, hashkey ,SEEK_SET); 
    fwrite(animal, sizeof(struct dogType), 1, f);
  }
}

void ver_registro (int n_reg){
	/* Validar que el número ingresado exista
         * Guardar el historial de la mascota en un archivo de texto
	 * y debe abrirse de forma automatica.
	 * Se puede ver y EDITAR el archivo en el editor de texto.
	 */
	/* struct datos *animal; */
	/* animal = ap; */
	/* printf("Nombre: %s\n", animal -> nombre) */
	/* printf("Tipo: %s\n", animal -> tipo) */
	/* printf("Edad: %i\n", animal -> edad) */
	/* printf("Raza: %s\n", animal -> raza) */
	/* printf("Estatura: %i\n", animal -> estatura) */
	/* printf("Peso: %.2f\n", animal -> peso) */
	/* printf("Genero: %c\n", animal -> genero) */
}

void borrar_registro (int n_reg){
	/* El registro es borrado del archivo, por lo que el
         * archivo debe reducir su tamaño.
	 */
}

void buscar_registro (char nombre[32]){
	/* Muestra todos los registros que coincidan completamente con
	 * el nombre. No se distingue de mayusculas.
	 */

}

void salir (){
	printf("Gracias por utilizar nuestra base de datos de animales. \n");
	printf("Hasta pronto. ");
	exit(-1);
}


void menu();

int main (){
  //menu();
  FILE * f;

  int i = hash("jimmy");
  
  f = fopen("j.dat", "w");
  fclose(f);

  f = fopen("j.dat", "r+");
  
  char n[] = "Jimmy";
  char s[] = "Alexander";

  fseek(f, 0L ,SEEK_SET);
  fwrite(n, sizeof(char), sizeof(n), f);
  fseek(f, (sizeof(n) + 40) ,SEEK_SET);
  fwrite(s, sizeof(char), sizeof(s), f);

  char j[500];
  
  fseek(f, 10 ,SEEK_SET);
  int num = fread(j, sizeof(char), 5, f);

  //printf("%s %i" , s, strlen(s));

  struct dogType uno  = {"jimmy", "kor", 20, "humn", 170, 47, 'M', -1};

  struct dogType dos  = {"Daniel", "kor", 20, "humn", 170, 47, 'M', -1};
   struct dogType tres  = {"jimmy", "kor", 20, "humn", 170, 47, 'M', -1};

  ingresar_registro(&uno, f);
  ingresar_registro(&dos,f);
  ingresar_registro(&tres,f);
}




void menu (){
  int n_reg;
  char opcion;
  struct dogType * animal;
  
  printf("Bienvenido a la base de datos de animales.\n Seleccione una opcion a continuacion: ");
  printf("1. Ingresar registro de un nuevo anmimal\n");
  printf("2. Ver registro de un animal existente\n");
  printf("3. Borrar registro de un animal\n");
  printf("4. Buscar registro de un animal existente\n");
  printf("5. Salir del programa\n");

  scanf("%c", &opcion);
  
  switch(opcion) {
  case '1' :
    
    animal = malloc(sizeof(struct dogType)); 
      
    printf("Ingrese el nombre del animal: \n");
    scanf("%s ", animal -> nombre);
    printf("Ingrese el tipo del animal: \n");
    scanf("%s ", animal -> tipo);
    printf("Ingrese la edad del animal: \n");
    scanf("%i ", &animal -> edad);
    printf("Ingrese la raza del animal: \n");
    scanf("%s ", animal -> raza);
    printf("Ingrese la estatura del animal: \n");
    scanf("%i ", &animal -> estatura);
    printf("Ingrese el peso del animal: \n");
    scanf("%f ", &animal -> peso);
    printf("Ingrese el genero del animal: \n");
    scanf("%c", &animal -> genero);

    animal -> next = -1 ;
    // ingresar_registro(animal);
    free(animal);
    
    printf("Se han ingresado los datos correctamente\n");
    break;
  case '2' :
    printf("Estos son los números de registro existentes: \n");
    /* Aqui debe imprimir los números de registro */
    printf("Ingrese el número de registro del animal para ver su historia clinica: \n");
    scanf("%i ", n_reg);
    ver_registro(n_reg);
    break;
  case '3' :
    printf("Estos son los números de registro existentes: \n");
    /* Aqui debe imprimir los números de registro */
    printf("Ingrese el número de registro del animal a ser eliminado de la base de datos: \n");
    scanf("%i ", n_reg);
    borrar_registro(n_reg);
    break;
  case '4' :
    printf("Ingrese el nombre del animal a buscar: \n");
    char bus_nombre [32];
    scanf("%s ", bus_nombre);
    buscar_registro(bus_nombre);
    break;
  case '5' :
    salir();
    break;
  default :
    printf ("Número inválido. Intente de nuevo. \n");
  }
}
