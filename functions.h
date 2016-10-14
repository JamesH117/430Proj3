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
	double len = sqrt(square(v[0] + square(v[1]) + square(v[2])));
	v[0] /= len;
	v[1] /= len;
	v[2] /= len;
}

static inline double vector_length(double* v){
    return sqrt(square(v[0])+square(v[1])+square(v[2]));

}
static inline double* mult_num_vector(double num, double* vvector, double* answer){
    answer[0] = num * vvector[0];
    answer[1] = num * vvector[1];
    answer[2] = num * vvector[2];
    return answer;
}
static inline double* add_vector(double* a, double* b, double* answer){
    answer[0] = a[0] + b[0];
    answer[1] = a[1] + b[1];
    answer[2] = a[2] + b[2];
    return answer;
}
static inline double* sub_vector(double* a, double* b, double* answer){
    //printf("%lf - %lf\n", a[0], b[0]);
    answer[0] = a[0] - b[0];
    //printf("%lf - %lf\n", a[1], b[1]);
    answer[1] = a[1] - b[1];
    //printf("%lf - %lf\n", a[2], b[2]);
    answer[2] = a[2] - b[2];
    return answer;
}
static inline void mult_vectors(double* a, double* b, double* c){
    c[0] = a[0]*b[0];
    c[1] = a[1]*b[1];
    c[2] = a[2]*b[2];
}
static inline int compare_objects(scene_object listo, scene_object pointero){
    //printf("Hello\n");
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
    //vvector is pointing from intersection point towards light, do I need to make it negative first and then dot product?
    vvector = mult_num_vector(-1, vvector, vvector);
    double num = dot_product(normal, vvector);
    //printf("num: %lf\n", num);
    double* a = malloc(sizeof(double)*3);
    mult_num_vector(num,normal, a);
    //printf("a[0]: %lf\n", a[0]);
    mult_num_vector(2,a,a);
    //printf("\na[0]: %lf", a[2]);

    sub_vector(vvector,a,reflection);

    free(a);
}
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

static inline double f_rad(scene_light a, double* vector_to_light){
    if(a.type == 'l'){ //point light
        double den = a.ra2*square(vector_length(vector_to_light));
        if(den == 0){
            return 1/square(vector_length(vector_to_light));
        }
        return 1/den;
    }
    if(a.type == 's'){ //spotlight
        double den = a.ra2*square(vector_length(vector_to_light)) + a.ra1*vector_length(vector_to_light) + a.ra0;
        if(den == 0){
            return 1/square(vector_length(vector_to_light));
        }
        return 1/den;
    }
}
static inline double diffuse_contribution(int color_index,double* object_diffuse_color, scene_light light_object, double* closest_normal, double* vector_to_light){
    return object_diffuse_color[color_index]*light_object.color[color_index]*(dot_product(closest_normal, vector_to_light));
}

static inline double specular_contribution(int color_index,double* object_specular_color, scene_light light_object, double* Ro_new, double* reflection_of_light_vector, double ns){
    return object_specular_color[color_index]*light_object.color[color_index]*power(dot_product(Ro_new, reflection_of_light_vector),ns);
}
