#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <termios.h>
#include <ctype.h>
#include <time.h>
#include <unistd.h>

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
    int key;
    int id;
    char nombre[32];
    char tipo[32];
    int edad;
    char raza[16];
    int estatura;
    float peso;
    char sexo;
    struct dogType * next;
};

void guardar(void *ap){
    
    FILE *apf;
    int r;
    apf = fopen("dataDogs.dat","a+");
    if(apf == NULL){perror("No se puede crear o abrir el archivo"); exit(-1);}
    r = fwrite(ap,sizeof(struct dogType),1,apf);
    if(r != 1){perror("No se puede escribir en el archivo"); exit(-1);}
    r = fclose(apf);
    if (r != 0) {perror("No se puede cerrar el flujo"); exit(-1);}
};

int main(){
    
    printf("¿Cuantos registros aleatorios desea Crear?: ");
    int reg;
    scanf("%i",&reg);
    struct dogType *perro;
    perro = malloc(sizeof(struct dogType));
    int count = 0;
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
                nombres[s].nombre[u] = ' ';
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
    
    //ITERACION RANDOM
    for(int i=0;i<reg;i++){
        
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
        perro->id = 0;
        //perro->key = convertir(perro->nombre);
        strncpy(perro->tipo,tipos[tipo].tipo,32);
        perro->edad = edad;
        strncpy(perro->raza,razas[raza].breed,16);
        perro->estatura = estatura;
        perro->peso = peso;
        perro->sexo = sexo;
        guardar(perro);
    }
}
