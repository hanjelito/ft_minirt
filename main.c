/* Un trazador de rayos simple */

#include <stdio.h>
#include <stdbool.h> /* Necesario para el tipo de datos booleano */

/* Ancho y alto de nuestra imagen */
#define WIDTH  800
#define HEIGHT 600

/* La estructura vectorial */
typedef struct{
      float x,y,z;
}vector;

/* La esfera */
typedef struct{
        vector pos;
        float  radius;
}sphere; 

/* El rayo */
typedef struct{
        vector start;
        vector dir;
}ray;

/* Reste dos vectores y devuelva el vector resultante */
/* (A1 - A2), (B1 - B2), (C1 - C2) */ 
vector vectorSub(vector *v1, vector *v2){
	vector result = {v1->x - v2->x, v1->y - v2->y, v1->z - v2->z };
	return result;
}

/* Multiplica dos vectores y devuelve el escalar resultante (producto escalar) */
float vectorDot(vector *v1, vector *v2){
	return v1->x * v2->x + v1->y * v2->y + v1->z * v2->z;
}


/* Compruebe si el rayo y la esfera se intersectan */
bool intersectRaySphere(ray *r, sphere *s){
	
	/* A = d.d, el producto escalar vectorial de la dirección */
	float A = vectorDot(&r->dir, &r->dir); 
	
	/* Necesitamos un vector que represente la distancia entre el inicio de
     * el rayo y la posición del círculo.
	 * Este es el término (p0 - c) 
	 */
	vector dist = vectorSub(&r->start, &s->pos);
	
	/* 2d.(p0 - c) */  
	float B = 2 * vectorDot(&r->dir, &dist);
	
	/* (p0 - c).(p0 - c) - r^2 */
	float C = vectorDot(&dist, &dist) - (s->radius * s->radius);
	
	/* Resolviendo el discriminante */
	float discr = B * B - 4 * A * C;
	
	/* Si el discriminante es negativo, no hay raíces reales.
     * Devuelve falso en ese caso, ya que el rayo no alcanza la esfera.
     * Devuelve verdadero en todos los demás casos (puede ser una o dos intersecciones)
	 */
	if(discr < 0)
		return false;
	else
		return true;
}

/* Salida de datos como archivo PPM */
void saveppm(char *filename, unsigned char *img, int width, int height){
	/* Puntero ARCHIVO */
	FILE *f;

	/* Abrir archivo para escribir */
	f = fopen(filename, "wb");

	/* Información del encabezado de PPM, incluido el tamaño de la imagen */
	fprintf(f, "P6 %d %d %d\n", width, height, 255);

	/* Escriba los datos de la imagen en el archivo: recuerde 3 bytes por píxel */
	fwrite(img, 3, width*height, f);

	/* Asegúrate de cerrar el archivo */
	fclose(f);
}

int main(int argc, char *argv[]){
	
	/* Datos de imagen */
	unsigned char img[3*WIDTH*HEIGHT];

	/* Nuestro rayo y una esfera */
	sphere s;
	ray r;
	
	/* x, y para 'resolución' de pantalla */
	int x,y;	

	/* Intersecta rayo / esfera o no */
	bool hit;

	/* posicion de la esfera */
	s.pos.x = 200;
	s.pos.y = 200;
	s.pos.z = 100;

	/* Radio de esfera */
	s.radius = 100;

	/* Dirección del rayo */
	r.dir.x = 0;
	r.dir.y = 0;
	r.dir.z = 1;

	/* Posición inicial del rayo, coordenada z */
	r.start.z = 0;

	/* Iterar cada píxel de nuestra pantalla */
	for(y=0;y<HEIGHT;y++){
		/* Establecer la coordenada-y de la posición inicial del rayo */
		r.start.y = y; 
		for(x=0;x<WIDTH;x++){
			/* Establecer la coordenada x de la posición inicial del rayo */
			r.start.x = x;

			/* Compruebe si el rayo se cruza con la esfera. */
			hit = intersectRaySphere(&r, &s);
			if(hit){
				img[(x + y*WIDTH)*3 + 0] = 255;
				img[(x + y*WIDTH)*3 + 1] = 0;
				img[(x + y*WIDTH)*3 + 2] = 0;
			}else{
				img[(x + y*WIDTH)*3 + 0] = 0;
				img[(x + y*WIDTH)*3 + 1] = 0;
				img[(x + y*WIDTH)*3 + 2] = 0;
			}
		}
	}

	saveppm("image.ppm", img, WIDTH, HEIGHT);

	return 0;
}