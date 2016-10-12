static inline double square(double v){
	return v*v;
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
    answer[0] = a[0] - b[0];
    answer[1] = a[1] - b[1];
    answer[2] = a[2] - b[2];
    return answer;
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
static inline void copy_object(scene_object coppy, scene_object original){
    coppy.type = original.type;
    coppy.diffuse_color = original.diffuse_color;
    coppy.specular_color = original.specular_color;
    coppy.position = original.position;
    coppy.normal = original.normal;
    coppy.radius = original.radius;
}
static inline void clamp(double c){
    if(c>1)
        c = 1;
    if(c<0)
        c = 0;
}

