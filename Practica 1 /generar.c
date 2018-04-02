#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <termios.h>
#include <ctype.h>
#include <time.h>
#include <unistd.h>
#include <locale.h>

long long pos[1000]; 

struct names{
    char nombre[32];
};
struct types{
    char tipo[32];
};
struct breeds{
    char breed[16];
};
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

const int MIL = 1000; 
const int DOGS = sizeof(struct dogType);

int hash(void * ap){  // Hash function 
    char * c;
    c = ap; 
    int tmp = 1;
    for( int i = 0; i < sizeof(ap) && c[i] >0  ; i++){
        if( c[i] >= 97 )  tmp += (c[i] - 32); 
        else tmp += c[i];
    }
    //printf("&&%s&& %i\n",c, tmp);
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
 

    numread = fread(tmp, sizeof(struct dogType), 1, f); 
    
    if( pos[ hash(animal -> nombre)] == 0) {
      //printf("No esta registrado %s %i \n", animal -> nombre, hash(animal -> nombre));
        fseek(f, hashkey ,SEEK_SET);
	pos[hash(animal -> nombre)] = hashkey; 
        fwrite(animal, sizeof(struct dogType), 1, f);
    }
    else
    {
      
        fseek(f, 0L ,SEEK_END);  // Look for the next free space 
        long long  postmp = ftell(f);
        if(postmp <= DOGS*1000)
        {
            postmp = DOGS * 1000; 
            fseek(f,postmp, SEEK_SET);
        }
        
        fwrite(animal, sizeof(struct dogType), 1, f);
        
        fseek(f, pos[hash(animal -> nombre)] ,SEEK_SET); // va a la pos del padre

	struct dogType * padre;
	padre = malloc(sizeof(struct dogType));

	fread(padre, sizeof(struct dogType), 1, f);
	padre -> next = postmp;  // le asigna el valor de la pos del byte  a next

	fseek(f, pos[hash(animal -> nombre)] ,SEEK_SET); // va a la pos del padre
        fwrite(padre, sizeof(struct dogType), 1, f);

	
	pos[hash(animal -> nombre)] = postmp;
	//printf("%i pos %s \n", pos[hash(animal -> nombre)], animal -> nombre );
        rewind(f); 
    }
    
    
    
    fclose(f); 
    
    
}


int main(){
  setlocale(LC_CTYPE,"Spanish");
  FILE * f; 
    f = fopen("dataDogs.dat","w+");
    fclose(f);
    printf("¿Cuantos registros aleatorios desea Crear?: ");
    int reg;
    scanf("%i",&reg);
    
    FILE *apf;
    
    apf = fopen("nombresMascotas.txt","r");
    if (apf == NULL) {
        perror("Can't open petnames file stream");
        exit(-1);
    }

    int s,u;
    struct names nombres[1716];
    for(s=0;s<1716;s++){
        fgets(nombres[s].nombre,32,apf);
        for (u=0;u<32;u++){         //Se mira si los nombres tienen saltos de línea
            if(nombres[s].nombre[u] == '\n'){
                nombres[s].nombre[u] = '\0';
            }
        }
    }

    apf = fopen("razas.txt","r");
    if (apf == NULL) {
        perror("Can't open breeds file stream");
        exit(-1);
    }
    struct breeds razas[52];
    for(s=0;s<52;s++){
        fgets(razas[s].breed,16,apf);
        for (u=0;u<16;u++){         //Se mira si las razas tienen saltos de línea
            if(razas[s].breed[u] == '\n'){
                razas[s].breed[u] = ' ';
            }
        }
    }

    struct types tipos[4];
    strncpy(tipos[0].tipo,"Perro",32); for (u=0;u<32;u++){ if(tipos[0].tipo[u] == '\n'){tipos[0].tipo[u] = ' ';}}
    strncpy(tipos[1].tipo,"Gato",32); for (u=0;u<32;u++){ if(tipos[1].tipo[u] == '\n'){tipos[1].tipo[u] = ' ';}}
    strncpy(tipos[2].tipo,"Loro",32); for (u=0;u<32;u++){ if(tipos[2].tipo[u] == '\n'){tipos[2].tipo[u] = ' ';}}
    strncpy(tipos[3].tipo,"Tortuga",32); for (u=0;u<32;u++){ if(tipos[3].tipo[u] == '\n'){tipos[3].tipo[u] = ' ';}}
    fclose(apf);
    
    printf("\nREGISTROS CARGADOS\n");
    
    char raza[16];
    char name[32];
    char tipo[32];


    struct dogType dos  = {"Daniel", "kor", 20, "humn", 170, 47, 'M', -1};

    //for(int i =0; i< 1000; i++) 
    // ingresar_registro(&dos);
    
    //ITERACION RANDOM
    for(int i=0;i<reg;i++){
        struct dogType *perro;
	perro = malloc(sizeof(struct dogType));
        //DECLARACION VARIABLES RANDOM
        int nombre = rand() % 1716;
        int tipo = rand() % 4;
        int edad = rand() % 20;
        int raza = rand() % 52;
        int estatura = rand() % 50;
        float peso = rand() % 60;
        char sexo = "HM"[random () % 2];
        
        //ASIGNACION EN dogType

        strncpy(perro->nombre,nombres[nombre].nombre,32);
	//printf("%s\n%i",perro->nombre, i);
        //perro->id = 0;
        //perro->key = convertir(perro->nombre);
        strncpy(perro->tipo,tipos[tipo].tipo,32);
        perro->edad = edad;
        strncpy(perro->raza,razas[raza].breed,16);
        perro->estatura = estatura;
        perro->peso = peso;
        perro->genero = sexo;
	perro->next = -1;
        ingresar_registro(perro);

	free(perro);
    }
}
