# define SCREEN_WIDTH		1080
# define SCREEN_HEIGHT		1080
# define INF				10000
# define SCREEN_OFFSET		200

enum 					    obj_type
{
	OBJ_PLANE,
	OBJ_SPHERE,
	OBJ_CYLINDER,
	OBJ_CONE
};

enum 					    light_type
{
	LGT_POINT,
	LGT_AMBIENT,
	LGT_DIRECTIONAL
};

typedef struct				s_roots
{
	float					t1;
	float					t2;
}							t_roots;

typedef struct				s_object_3d
{
	int						height;
	int						type;
	int						specular;
	float					angle;
	float					reflective;
	float					radius;
	int3					color;
	float3					start_point;
	float3					normal;
	float3					rot;
}							t_object_3d;

typedef struct				s_light
{
	int						type;
	float					intensity;
	int3					color;
	float3					start_point;
}							t_light;

typedef struct				s_camera
{
	int						anti_aliasing;
	float3					pos;
	float3					rotation;
}							t_camera;

typedef struct				s_inter
{
	float					closest_t;
	__constant t_object_3d	*object;
}							t_inter;

typedef struct				s_rt
{
	int						count_objects;
	int						count_lights;
	t_camera				camera;
}							t_rt;

void	                    c_clamp(int3 *c);

float3	                    rotate_x(float3 t, float3 rotation);
float3	                    rotate_y(float3 t, float3 rotation);
float3	                    rotate_z(float3 t, float3 rotation);
float3	                    __attribute__((overloadable)) rotate(float3 t, float3 rotation);
float3	                    reflected_ray(float3 v1, float3 v2);
float3	                    reflected_ray_2(float3 v1, float3 v2);
float3                      vec_mult(float3 v, float k);
float3                      get_normal(float3 p, t_inter inter);

float                       compute_lighting(t_rt *rt, float3 p, float3 n, float3 v, float s, __constant t_object_3d *objects, __constant t_light *lights);
float 	                    vector_magnitude(float3 v);
float	                    __attribute__((overloadable)) dot(float3 t1, float3 t2);
float 	                    get_len(float k1, float k2, float k3);

t_roots					    intersect_cone(t_object_3d cone, float3 o, float3 point);
t_roots					    intersect_sphere(t_object_3d sphere, float3 o, float3 point);
t_roots					    intersect_cylinder(t_object_3d cylinder, float3 o, float3 point);
t_roots					    intersect_plane(t_object_3d plane, float3 o, float3 point);

t_inter	                    closest_inter(t_rt *rt, float3 o, float3 point, float min, float max, __constant t_object_3d *objects);

int3	                    color_multiplication(int3 color, float k);
int3	                    ray_tracer(t_rt *rt, float3 start, float3 point, float min, float max, __constant t_object_3d *objects, __constant t_light *lights);
int3                        get_ray_color(t_rt *rt, float i, float j, __constant t_object_3d *objects, __constant t_light *lights);
int3	                    get_middle_color(int3 c1, int3 c2);
int3                        anti_aliasing(t_rt *rt, float i, float j, __constant t_object_3d *objects, __constant t_light *lights);

int		                    get_color(int r, int g, int b);

int		get_color(int r, int g, int b)
{
	return ((r & 0x0ff) << 16) | ((g & 0x0ff) << 8) | (b & 0x0ff);
}

void	c_clamp(int3 *c)
{
	if (c->x >= 256)
		c->x = 255;
	else if (c->x < 0)
		c->x = 0;
	if (c->y >= 256)
		c->y = 255;
	else if (c->y < 0)
		c->y = 0;
	if (c->z >= 256)
		c->z = 255;
	else if (c->z < 0)
		c->z = 0;
}

int3	color_multiplication(int3 color, float k)
{
	color.x = (int)((float)color.x * k);
	color.y = (int)((float)color.y * k);
	color.z = (int)((float)color.z * k);
	c_clamp(&color);
	return (color);
}

int3	get_middle_color(int3 c1, int3 c2)
{
    int3    c;
	float	r;
	float	g;
	float	b;

	r = sqrt(((pow((float)c1.r, (float)2) + pow((float)c2.r, (float)2)) / 2.0));
	g = sqrt(((pow((float)c1.g, (float)2) + pow((float)c2.g, (float)2)) / 2.0));
	b = sqrt(((pow((float)c1.b, (float)2) + pow((float)c2.b, (float)2)) / 2.0));
	c.r = (int)r;
	c.g = (int)g;
	c.b = (int)b;
	return (c);
}

float3	rotate_x(float3 t, float3 rotation)
{
	float3	v;

	v.x = t.x;
	v.y = t.y * cos(rotation.x * M_PI / 180) + t.z *
											   sin(rotation.x * M_PI / 180);
	v.z = t.z * cos(rotation.x * M_PI / 180) - t.y *
											   sin(rotation.x * M_PI / 180);
	return (v);
}

float3	rotate_y(float3 t, float3 rotation)
{
	float3	v;

	v.x = t.x * cos(rotation.y * M_PI / 180) - t.z *
											  sin(rotation.y * M_PI / 180);
	v.y = t.y;
	v.z = t.z * cos(rotation.y * M_PI / 180) + t.x *
											  sin(rotation.y * M_PI / 180);
	return (v);
}

float3	rotate_z(float3 t, float3 rotation)
{
	float3	v;

	v.x = t.x * cos(rotation.z * M_PI / 180) + t.y *
											   sin(rotation.z * M_PI / 180);
	v.y = t.y * cos(rotation.z * M_PI / 180) - t.x *
											   sin(rotation.z * M_PI / 180);
	v.z = t.z;
	return (v);
}

float3	__attribute__((overloadable))	rotate(float3 t, float3 rotation)
{
	t = rotate_x(t, rotation);
	t = rotate_y(t, rotation);
	t = rotate_z(t, rotation);
	return (t);
}

float	__attribute__((overloadable))   dot(float3 t1, float3 t2)
{
	return (t1.x * t2.x + t1.y * t2.y + t1.z * t2.z);
}

float 	vector_magnitude(float3 v)
{
	return (v.x * v.x + v.y * v.y + v.z * v.z);
}

float 	get_len(float k1, float k2, float k3)
{
	float t1;
	float t2;
	float d;

	d = k2 * k2 - 4 * k1 * k3;
	t1 = (-1 * k2 - sqrt((float)d)) / (2 * k1);
	t2 = (-1 * k2 + sqrt((float)d)) / (2 * k1);
	if (d < 0)
		return (-1);
	else if (d == 0)
		return (t1);
	else if (t1 > t2)
		return (t2);
	else
		return (t1);
}

t_roots	intersect_cone(t_object_3d cone, float3 o, float3 point)
{
	t_roots		ks;
    float		d;
    float		k1;
    float		k2;
    float 		k3;
    float       k;
    float2      m;
    float3		oc;

    ks.t1 = INF;
    ks.t2 = INF;
    oc = o - cone.start_point;
    if (cone.angle < 0)
        k = 1 - cone.angle * cone.angle;
    else
        k = 1 + cone.angle * cone.angle;
    cone.normal = rotate(cone.normal, cone.rot);
    k1 = dot(point, point) - k * pow((float)dot(point, cone.normal), (float)2);
    k2 = (dot(point, oc) - k * dot(point, cone.normal) * dot(oc, cone.normal)) * 2;
    k3 = dot(oc, oc) - k * pow((float)dot(oc, cone.normal), (float)2);
    d = k2 * k2 - 4 * k1 * k3;
    if (d < 0)
        return (ks);
    ks.t1 = (-1 * k2 - sqrt((float)d)) / (2 * k1);
    ks.t2 = (-1 * k2 + sqrt((float)d)) / (2 * k1);
    if (cone.height == 0)
        return (ks);
    m = (float2){dot(point, cone.normal) * ks.t1 + dot(oc, cone.normal), dot(point, cone.normal) * ks.t2 + dot(oc, cone.normal)};
    if (cone.height > 0)
    {
        if (!(m.x > 0 && m.x < cone.height))
            ks.t1 = INF;
        if (!(m.y > 0 && m.y < cone.height))
            ks.t2 = INF;
    }
    if (cone.height < 0)
    {
        if (!(m.x < 0 && m.x > cone.height))
            ks.t1 = INF;
        if (!(m.y < 0 && m.y > cone.height))
            ks.t2 = INF;
    }
    return (ks);
}

t_roots	intersect_sphere(t_object_3d sphere, float3 o, float3 point)
{
	t_roots		ks;
	float		d;
	float		k1;
	float		k2;
	float 		k3;
	float3		oc;

	ks.t1 = INF;
	ks.t2 = INF;
	oc = o - sphere.start_point;
	k1 = dot(point, point);
	k2 = 2.0f * dot(oc, point);
	k3 = dot(oc, oc) - pow((float)sphere.radius, 2.0f);
	d = k2 * k2 - 4 * k1 * k3;
	if (d < 0)
		return (ks);
    ks.t1 = (-k2 + sqrt((float)d)) / (2.0f * k1);
    ks.t2 = (-k2 - sqrt((float)d)) / (2.0f * k1);
	return (ks);
}

t_roots	intersect_cylinder(t_object_3d cylinder, float3 o, float3 point)
{
	t_roots		ks;
	float		d;
	float		k1;
	float		k2;
	float 		k3;
	float2      m;
	float3		oc;
	float3		va;
	float3		a;
	float3		b;

	ks.t1 = INF;
	ks.t2 = INF;
	oc = o - cylinder.start_point;
	cylinder.normal = rotate(cylinder.normal, cylinder.rot);
	va = normalize(cylinder.start_point - cylinder.normal);
	a = point - vec_mult(va, dot(point, va));
	b = oc - vec_mult(va, dot(oc, va));
	k1 = dot(a, a);
	k2 = 2.0 * dot(a, b);
	k3 = dot(b, b) - pow((float)cylinder.radius, (float)2);
	d = k2 * k2 - 4 * k1 * k3;
	if (d < 0)
		return (ks);
	ks.t1 = (-1 * k2 - sqrt((float)d)) / (2 * k1);
	ks.t2 = (-1 * k2 + sqrt((float)d)) / (2 * k1);
	if (cylinder.height == 0)
	    return (ks);
	m = (float2){dot(point, cylinder.normal) * ks.t1 + dot(oc, cylinder.normal), dot(point, cylinder.normal) * ks.t2 + dot(oc, cylinder.normal)};
	if (!(m.x >= 0 && m.x < cylinder.height))
	    ks.t1 = INF;
    if (!(m.y >= 0 && m.y < cylinder.height))
        ks.t2 = INF;
	return (ks);
}

t_roots	intersect_plane(t_object_3d plane, float3 o, float3 point)
{
	t_roots	ks;
	float	d;
	float3	oc;

	ks.t1 = INF;
	ks.t2 = INF;
	oc = o - plane.start_point;
	plane.normal = rotate(plane.normal, plane.rot);
	if (dot(plane.normal, point) != 0)
	{
		d = -dot(plane.normal, oc) / dot(plane.normal, point);
		if (d > 0.0001)
		{
			ks.t1 = d;
			ks.t2 = d;
		}
	}
	return (ks);
}

float3  vec_mult(float3 v, float k)
{
    v.x *= k;
    v.y *= k;
    v.z *= k;
    return (v);
}

float3	reflected_ray(float3 r, float3 n)
{
    float3 v;

    v = vec_mult(n, 2.0 * dot(n, r));
	return (v - r);
}

float 	compute_lighting(t_rt *rt, float3 p, float3 n, float3 v, float s, __constant t_object_3d *objects, __constant t_light *lights)
{
	t_inter	inter;
	float	i;
	float 	r_dot;
	float 	n_dot;
	float 	max;
	int		j;
	float3	l;
	float3	r;

	i = 0.0f;
	j = -1;
	while (++j < rt->count_lights)
	{
		if (lights[j].type == LGT_AMBIENT)
			i += lights[j].intensity;
		else
		{
			if (lights[j].type == LGT_POINT)
			{
				l = lights[j].start_point - p;
				max = 1.0f;
			}
			else
			{
				l = lights[j].start_point;
				max = INF;
			}

			inter = closest_inter(rt, p, l, 0.001f, max, objects);
			if (inter.object != 0x0)
			    continue ;
            n_dot = dot(n, l);
            if (n_dot > 0.0f)
                i += lights[j].intensity * n_dot / (length(n) * length(l));
            if (s > 0)
            {
                r = reflected_ray(l, n);
                r_dot = dot(r, v);
                if (r_dot > 0.0f)
                    i += lights[j].intensity * pow((float)(r_dot / (length(r) * length(v))), (float)s);
            }
		}
	}
	return (i);
}

t_inter	closest_inter(t_rt *rt, float3 o, float3 point, float min, float max, __constant t_object_3d *objects)
{
	t_inter		            inter;
	t_roots		            ks;
	int			            i;

	inter.closest_t = INF;
    inter.object = 0;
    i = -1;
    while (++i < rt->count_objects)
    {
        if (objects[i].type == OBJ_SPHERE)
            ks = intersect_sphere(objects[i], o, point);
        else if (objects[i].type == OBJ_PLANE)
            ks = intersect_plane(objects[i], o, point);
        else if (objects[i].type == OBJ_CYLINDER)
            ks = intersect_cylinder(objects[i], o, point);
        else if (objects[i].type == OBJ_CONE)
            ks = intersect_cone(objects[i], o, point);
        if (ks.t1 < inter.closest_t && ks.t1 >= min && ks.t1 < max)
        {
            inter.closest_t = ks.t1;
            inter.object = &objects[i];
        }
        if (ks.t2 < inter.closest_t && ks.t2 >= min && ks.t2 < max)
        {
            inter.closest_t = ks.t2;
            inter.object = &objects[i];
        }
    }
	return (inter);
}

float3  get_normal(float3 p, t_inter inter)
{
    float3	n;
    float3	os;
    float3	proj;

    if (inter.object->type == OBJ_SPHERE)
    {
        n = p - inter.object->start_point;
        return (normalize(n));
    }
    if (inter.object->type == OBJ_CONE || inter.object->type == OBJ_CYLINDER)
    {
    	os = normalize(inter.object->normal - inter.object->start_point);
    	n = p - inter.object->start_point;
    	proj = vec_mult(os, dot(n, os));
    	n = n - proj;
    	return (normalize(n));
    }
    return (inter.object->normal);
}

int3	ray_tracer(t_rt *rt, float3 start, float3 point, float min, float max, __constant t_object_3d *objects, __constant t_light *lights)
{
    t_inter                 inter;
    float3                  p;
    float3                  n;
    float                   diffuse;
    int3                    l_c;
    int3                    r_c;

    inter = closest_inter(rt, start, point, min, max, objects);
    if (inter.object == 0)
        return ((int3){0, 0, 0});
    p = start + (point * inter.closest_t);
    n = get_normal(p, inter);
    r_c = (int3){0, 0, 0};
    diffuse = compute_lighting(rt, p, n, vec_mult(point, -1.0f), inter.object->specular, objects, lights);
    l_c = color_multiplication(inter.object->color, diffuse);
    return(l_c);
}

int3    get_ray_color(t_rt *rt, float i, float j, __constant t_object_3d *objects, __constant t_light *lights)
{
	float3	p;

	p = (float3){(j - SCREEN_WIDTH / 2) * 1.0 / SCREEN_WIDTH,
					 (i - SCREEN_HEIGHT / 2) * 1.0 / SCREEN_HEIGHT, 1.0};
	p = rotate(p, rt->camera.rotation);
	return (ray_tracer(rt, rt->camera.pos, p, 1, INF, objects, lights));
}

int3    anti_aliasing(t_rt *rt, float i, float j, __constant t_object_3d *objects, __constant t_light *lights)
{
	float 	jj;
	float 	ti;
	float 	tj;
	int3    color;

	jj = j;
	color = get_ray_color(rt, i, j, objects, lights);
	ti = i + 1;
	tj = j + 1;
	i -= 1;
	while (i < ti)
	{
		j = jj - 1;
		while (j < tj)
		{
		    j += 1.0 / rt->camera.anti_aliasing;
			color = get_middle_color(color, get_ray_color(rt, i, j, objects, lights));
		}
		i += 1.0 / rt->camera.anti_aliasing;
	}
	return (color);
}

__kernel void   render(t_rt rt, __global int *color, __constant t_object_3d *objects, __constant t_light *lights)
{
    int j = get_global_id(0);
    int i = get_global_id(1);
    int3 col;

    if (rt.camera.anti_aliasing > 1)
        col = anti_aliasing(&rt, i, j, objects, lights);
    else
        col = get_ray_color(&rt, i, j, objects, lights);
	color[(j + SCREEN_OFFSET) + i * (SCREEN_WIDTH + SCREEN_OFFSET * 2)] = get_color(col.x, col.y, col.z);
}