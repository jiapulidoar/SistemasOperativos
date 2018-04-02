#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>
const int MIL = 1000; 

char* strlwr(char* s)
{
    char* tmp = s;

    for (;*tmp;++tmp) {
        *tmp = tolower((unsigned char) *tmp);
    }

    return s;
}

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

const int DOGS = sizeof(struct dogType);


int hash(void * ap){  // Hash function 
    char * c;
    c = ap; 
    int tmp = 1;
    for( int i = 0; i < sizeof(ap) && c[i] > 0 ; i++){
        if( c[i] >= 97 )  tmp += (c[i] - 32); 
        else tmp += c[i];
    }
   // printf("$$$%s$$$ %i \n",c, tmp);
    return (tmp % MIL) ; 
}



void ingresar_registro(void * ap){
    
    FILE * f; 
    
    f = fopen("dataDogs.dat", "r+");
    
    struct dogType * animal;
    int hashkey, numread = 0 , hashi;
    
    animal = ap;
    hashkey = hash(animal -> nombre) * sizeof(struct dogType); // @hashKey stores the memor position  of the current dogTypeStruct 
    
    struct dogType * tmp;
    tmp = malloc(sizeof(struct dogType));
    
    hashi = hashkey;
    fseek(f,hashi, SEEK_SET);
    
    while( numread = fread(tmp, sizeof(struct dogType), 1, f) == 1 && tmp -> next != 0 )
    {
        if(tmp -> next  == -1)
            break;
        hashi = tmp -> next; 
        fseek(f,hashi, SEEK_SET);
    }
    
    
    //printf("numread: %i \n", numread);
    
    if( numread == 0 ) {
      //printf("No esta registrado");
        fseek(f, hashkey ,SEEK_SET); 
        fwrite(animal, sizeof(struct dogType), 1, f);
    }
    else
    {
        fseek(f, 0L ,SEEK_END);  // Look for the next free space 
        long  pos = ftell(f);
        if(pos <= DOGS*1000)
        {
            pos = DOGS * 1000; 
            fseek(f,pos, SEEK_SET);
        }
        //printf("%i pos \n", pos);
        tmp -> next = pos;  // le asigna el valor de la pos del byte  a next
        fwrite(animal, sizeof(struct dogType), 1, f);
        
        fseek(f, hashi ,SEEK_SET); // vuelve a la pos del padre
        fwrite(tmp, sizeof(struct dogType), 1, f);
        rewind(f); 
    }
    
    
    
    fclose(f); 
    
    
}

void print_registro(void * ap, int key ){  // key = memory position 
    struct dogType * animal;
    animal = ap;

    printf("Numero registro: %i\n\t", key/100);
    printf("Nombre: %s\t", animal -> nombre);
    printf("hashkey: %i  \t", hash(animal -> nombre));
    printf("Tipo: %s\t", animal -> tipo) ;
    printf("Edad: %i\t", animal -> edad);
    printf("Raza: %s\t", animal -> raza) ;
    printf("Estatura: %i\t", animal -> estatura);
    printf("Peso: %.2f\t", animal -> peso) ;
    printf("Genero: %c\n", animal -> genero);
    printf("Next: %i\n", animal -> next);
}

void get_registro (int * n_reg){ 
    
    FILE * f; 
    int key = 0, hash = *n_reg ; 
    f = fopen("dataDogs.dat", "r+");
    
    struct dogType * animal;
    animal = malloc( sizeof(struct dogType));

    key = hash *DOGS;
    
    fseek(f, key , SEEK_SET );
    fread(animal, sizeof(struct dogType), 1, f); 
    
    print_registro( animal,  key); 
    
    free(animal);
    fclose(f); 

}



void borrar_registro (int * n_reg){
    FILE * f; 
    int key = 0, hash = * n_reg  ; 
    char cero = 0b0000;
    f = fopen("dataDogs.dat", "r+");
    
    struct dogType * animal;
    animal = malloc( sizeof(struct dogType));
    
    key = hash * DOGS; 
    
    printf("%i ", key);
    
    fseek(f, key, SEEK_SET); 
    fread(animal, sizeof(struct dogType), 1 ,f );
    
    if(animal ->  next == -1 ){
        

        fseek(f, key, SEEK_SET); 
        fwrite(&cero, 1, DOGS, f);   // Revisar buscar ultimo espacio libre
        
    }else{
        int keytmp = animal -> next; 
        struct dogType * hijo;
        
        hijo = malloc( sizeof(struct dogType));
        
        
        //printf(" Hijo pos %i", keytmp);
        
        fseek(f, keytmp, SEEK_SET);
        fread(hijo, sizeof(struct dogType), 1 ,f );
        
        fseek(f, keytmp, SEEK_SET);
        fwrite(&cero, 1, DOGS, f);
        
        fseek(f, key, SEEK_SET);
        fwrite(hijo, DOGS,1, f);
        
        //printf(" Mira aqui %i", hijo -> next);
    }
    free(animal);
    
    fclose(f);
    
}


int num_reg(){  // Calcula numero de registros
    
    FILE * f; 
    int key = 0, num_reg = 0  ; 
    f = fopen("dataDogs.dat", "r+");
    
    fseek(f,0L, SEEK_END); 
    num_reg = ftell(f);
    
    int cien = 100,count = 0 ; 
    
    for(int i = 0; i< 1000; i++){
        
        fseek(f, cien*i, SEEK_SET);
        char c; 
        fread(&c, 1, 1 ,f);
        if(c != 0 )
            count ++;
    }
    
    
    
    return (num_reg-100*1000)/100 +  count;
}

void buscar_registro (void * ap){
    
    FILE * f; 
    int key = 0 ; 
    f = fopen("dataDogs.dat", "r+");
    
    int bool = 0;
    struct dogType * animal;
    animal = malloc( sizeof(struct dogType));
    
    key = hash(ap) * DOGS; 
    
    do {  
        fseek(f, key , SEEK_SET ); 
        fread(animal, sizeof(struct dogType), 1, f); 

       
	//printf("%i #%s#%s# \n",  strcmp(ap,animal -> nombre), ap, animal ->nombre ); 

	char  tmp1[32]   , tmp2[32] ;
	strcpy(tmp1, ap);
	strcpy(tmp2, animal -> nombre); 
	if( strcmp( strlwr(tmp1) ,strlwr(tmp2)) == 0 ) {
        	print_registro( animal,  key); 
		bool = 1;
	}
        
        key = animal -> next;
        
    } while( animal -> next != -1 && animal -> next != 0 ); 
	
    if(!bool){
	printf("Lo sentimos pero %s no arroja ningún resultado.\n", ap);
	}    

    free(animal);
    fclose(f); 
}

void salir (){
    printf("Gracias por utilizar nuestra base de datos de animales. \n");
    printf("Hasta pronto. ");
    exit(-1);
}


void menu();

int main (){
    setlocale(LC_ALL, "");
    FILE * f;
    
    int i = hash("jimmy");
    //f = fopen("dataDogs.dat", "w");
    //fclose(f);
    
    f = fopen("dataDogs.dat", "r+");
    
    printf("%i ", ftell(f)); 
    
    
    
    struct dogType uno  = {"Jimmy", "kor", 20, "humn", 170, 47, 'M', -1};
    
    struct dogType dos  = {"Daniel", "kor", 20, "humn", 170, 47, 'M', -1};
    struct dogType tres  = {"jImmy", "kor", 20, "humn", 170, 47, 'M', -1};
    /*
    fclose(f);
    ingresar_registro(&uno);
    ingresar_registro(&tres);
    ingresar_registro(&tres);
    ingresar_registro(&tres);

    for(int i =0; i< 1000; i++) 
      ingresar_registro(&dos);
    
    
    struct dogType * animal;
    animal = malloc(sizeof(struct dogType));
    
    char nombre[] = "jimmy";
    buscar_registro(nombre);

    */ 
    menu();
    
}




void menu (){
  int n_reg;
    char opcion;
    struct dogType * animal;
    
    printf("\e[2J\e[H");
    
    
    printf("Bienvenido a la base de datos de animales.\n Seleccione una opcion a continuacion: \n");
    printf("1. Ingresar registro de un nuevo anmimal\n");
    printf("2. Ver registro de un animal existente\n");
    printf("3. Borrar registro de un animal\n");
    printf("4. Buscar registro de un animal existente\n");
    printf("5. Salir del programa\n");
    
    
    scanf(" %c", &opcion);
    switch(opcion) {
        case '1' :
            
            animal = malloc(sizeof(struct dogType)); 
            
            printf("Ingrese el nombre del animal: \n");
            scanf("%s", animal -> nombre);
            printf("Ingrese el tipo del animal: \n");
            scanf("%s", animal -> tipo);
            printf("Ingrese la edad del animal: \n");
            scanf("%i", &animal -> edad);
            printf("Ingrese la raza del animal: \n");
            scanf("%s", animal -> raza);
            printf("Ingrese la estatura del animal: \n");
            scanf("%i", &animal -> estatura);
            printf("Ingrese el peso del animal: \n");
            scanf("%f", &animal -> peso);
            printf("Ingrese el genero del animal: \n");
            scanf("%c%*c", &animal -> genero);
            
            animal -> next = -1 ;
            ingresar_registro(animal);
            free(animal);
            
            printf("Se han ingresado los datos correctamente\n");
            
            printf("Pulse una recla para continuar..................\n");
            
            getchar();
            break;
        case '2' :
            
            printf("Estos son los números de registro existentes: %i \n", num_reg());
            /* Aqui debe imprimir los números de registro */
            printf("Ingrese el número de registro del animal para ver su historia clinica: \n");
            
            scanf("%i%*c",&n_reg);
	      get_registro(&n_reg);
            
            printf("Pulse una recla para continuar..................\n");
            
            getchar();
            break;
        case '3' :
            printf("Estos son los números de registro existentes: %i \n", num_reg());
            
            printf("Ingrese el número de registro del animal a ser eliminado de la base de datos: \n");
            scanf("%i", &n_reg);
            borrar_registro(&n_reg);
            printf("Registro borrado exitosamente \n");
            
            
            printf("Pulse una recla para continuar..................\n");
            
            getchar();
            break;
        case '4' :
            printf("Ingrese el nombre del animal a buscar: \n");
            char bus_nombre [32];
            scanf("%s%*c", bus_nombre);
            buscar_registro(bus_nombre);

            printf("Pulse una recla para continuar..................\n");
            
            getchar();
            
            break;
        case '5' :
            salir();
            break;
        default :
            printf ("Número inválido. Intente de nuevo. \n");
        
    }
    printf("\e[2J\e[H");
    
    menu ();
        
}
