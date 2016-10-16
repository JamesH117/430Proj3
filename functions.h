static inline double square(double v){
	return v*v;
}
static inline double power(double n, double r){
    double a = n;
    while(r!=1){
        a = a*n;
        r-=1;
    }
    return a;
}
static inline void normalize(double* v){
	double len = sqrt(square(v[0]) + square(v[1]) + square(v[2]));
	v[0] /= len;
	v[1] /= len;
	v[2] /= len;
}
static inline double vector_length(double* v){
    return sqrt(square(v[0])+square(v[1])+square(v[2]));

}
static inline void scale_vector(double scaler, double* vvector, double* answer){
    answer[0] = scaler * vvector[0];
    answer[1] = scaler * vvector[1];
    answer[2] = scaler * vvector[2];
}
static inline void add_vector(double* a, double* b, double* answer){
    answer[0] = a[0] + b[0];
    answer[1] = a[1] + b[1];
    answer[2] = a[2] + b[2];
}
static inline void sub_vector(double* a, double* b, double* answer){
    answer[0] = a[0] - b[0];
    answer[1] = a[1] - b[1];
    answer[2] = a[2] - b[2];
}
static inline void mult_vectors(double* a, double* b, double* answer){
    answer[0] = a[0]*b[0];
    answer[1] = a[1]*b[1];
    answer[2] = a[2]*b[2];
}
static inline int compare_objects(scene_object listo, scene_object pointero){
    if(listo.type != pointero.type) return -1;
    if(listo.diffuse_color != pointero.diffuse_color) return -1;
    if(listo.specular_color != pointero.specular_color) return -1;
    if(listo.position != pointero.position) return -1;
    if(listo.normal != pointero.normal) return -1;
    if(listo.radius != pointero.radius) return -1;
    return 0;
}
static inline scene_object copy_object(scene_object coppy, scene_object original){
    //printf("orig type: %c\n", original.type);
    coppy.type = original.type;
    //printf("coppy type: %c\n", coppy.type);
    coppy.diffuse_color = original.diffuse_color;
    coppy.specular_color = original.specular_color;
    coppy.position = original.position;
    coppy.normal = original.normal;
    coppy.radius = original.radius;
    return coppy;
}
static inline double clamp(double c){
    if(c>1)
        c = 1;
    if(c<0)
        c = 0;
        return c;
}
static inline double dot_product(double* a, double* b){
    return (a[0]*b[0] + a[1]*b[1] + a[2]*b[2]);
}
static inline void vector_reflect(double* normal, double* vvector, double* reflection){
    normalize(normal); //normalize normal just incase it is not already normalized
    //vvector is pointing from intersection point towards light, do I need to make it negative first and then dot product?
    //If vvector is not poitning to the initial point of the normal vector, i need to inverse vvector before reflecting it
    scale_vector(1, vvector, vvector);
    double num = dot_product(normal, vvector); //Dot product between normal and vector to reflect
    double* a = malloc(sizeof(double)*3);

    scale_vector(num,normal, a); //Scale the normal with that dotproduct
    scale_vector(2,a,a);        //Scale that new vector with 2
    sub_vector(vvector,a,reflection);  //Subtract the new scaled vector from the vector to reflect
    //Reflection should now be the reflection of vvector
    free(a);//Free the memory used for this equation
}

//F_ang is not done at all
static inline double f_ang(scene_light a){
    if(a.type == 'l') return 1;
    //if(alpha > 0);
    /*else{
        double num = dot_product(v0, v1);\
        num = power(num, aa0);
        return num;
    }*/
    return 1;
}

static inline double f_rad(scene_light a, double* Ro_new){
    double* vector_to_light = malloc(sizeof(double)*3);
    double answer;

    //a.position - Ro_new = vector_to_light
    if(a.type == 'l'){ //point light
        sub_vector(a.position, Ro_new, vector_to_light);
        double den = a.ra2*square(vector_length(vector_to_light));
        if(den == 0){
            answer = 1/square(vector_length(vector_to_light));
            free(vector_to_light);
            return answer;
        }
        else{
            free(vector_to_light);
            return 1/den;
        }
    }
    if(a.type == 's'){ //spotlight
        sub_vector(a.position, Ro_new, vector_to_light);
        double den = a.ra2*square(vector_length(vector_to_light)) + a.ra1*vector_length(vector_to_light) + a.ra0;
        if(den == 0){
            answer = 1/square(vector_length(vector_to_light));
            free(vector_to_light);
            return answer;
        }
        else{
            free(vector_to_light);
            return 1/den;
        }
    }
}
static inline double diffuse_contribution(int index,double* obj_diff_color, scene_light light_obj, double* closest_normal, double* vector_to_light){
    normalize(closest_normal); //Normalize incase it is not already normalized
    return obj_diff_color[index]*light_obj.color[index]*(dot_product(closest_normal, vector_to_light));
}
static inline double specular_contribution(int index, double* obj_spec_color, scene_light light_obj, double* view_vector, double* reflection_of_light_vector, double ns){
    return obj_spec_color[index]*light_obj.color[index]*power(dot_product(view_vector, reflection_of_light_vector),ns);
}

static inline void print_light(scene_light a){
    printf("color: %lf, %lf %lf\n", a.color[0], a.color[1], a.color[2]);
    printf("position: %lf, %lf %lf\n", a.position[0], a.position[1], a.position[2]);
    printf("\n\n");
}



static inline void free_obj_list(scene_object *A, int index, int sizeof_obj){
    int k;
    for(k=0; k<= index; k+= sizeof_obj){
            free(A[k].diffuse_color);
            free(A[k].specular_color);
            free(A[k].position);

            if(A[k].type == 'p'){
                free(A[k].normal);
            }

    }
}
static inline void free_light_list(scene_light *A, int index, int sizeof_light){
    int k;
    for(k=0; k<= index; k+= sizeof_light){
        free(A[k].color);
        free(A[k].position);
        if(A[k].type == 's'){
            free(A[k].direction);
        }
    }
}
