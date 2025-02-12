#include "polygon_c.h"
#include "gdstk/polygon.hpp"
#include "gdstk/vec.hpp"

using namespace gdstk;




struct GDSTK_PropertyValue {
    gdstk::PropertyValue* value;
};

struct GDSTK_Polygon {
    Polygon polygon;
};

extern "C" {

// Getters for Polygon fields
uint64_t gdstk_polygon_get_tag(const GDSTK_Polygon* polygon) {
    if (!polygon) {
        fprintf(stderr, "Warning: gdstk_polygon_get_tag received null polygon parameter\n");
        return 0;
    }
    return polygon->polygon.tag;
}

uint64_t gdstk_polygon_point_array_count(const GDSTK_Polygon* polygon) {
    if (!polygon) {
        fprintf(stderr, "Warning: gdstk_polygon_point_array_count received null polygon parameter\n");
        return 0;
    }
    return polygon->polygon.point_array.count;
}

GDSTK_Array gdstk_polygon_get_point_array(const GDSTK_Polygon* polygon) {
    if (!polygon) {
        fprintf(stderr, "Warning: gdstk_polygon_get_point_array received null polygon parameter\n");
        constexpr GDSTK_Array array = {nullptr};
        return array;
    }
    const GDSTK_Array array = {
        reinterpret_cast<Array<void*>*>(const_cast<Array<Vec2>*>(&polygon->polygon.point_array))
    };
    return array;
}

void* gdstk_polygon_get_owner(const GDSTK_Polygon* polygon) {
    if (!polygon) {
        fprintf(stderr, "Warning: gdstk_polygon_get_owner received null polygon parameter\n");
        return nullptr;
    }
    return polygon->polygon.owner;
}

// Repetition getters
int gdstk_polygon_get_repetition_type(const GDSTK_Polygon* polygon) {
    if (!polygon) {
        fprintf(stderr, "Warning: gdstk_polygon_get_repetition_type received null polygon parameter\n");
        return 0;
    }
    return static_cast<int>(polygon->polygon.repetition.type);
}

uint64_t gdstk_polygon_get_repetition_columns(const GDSTK_Polygon* polygon) {
    if (!polygon) {
        fprintf(stderr, "Warning: gdstk_polygon_get_repetition_columns received null polygon parameter\n");
        return 0;
    }
    return polygon->polygon.repetition.columns;
}

uint64_t gdstk_polygon_get_repetition_rows(const GDSTK_Polygon* polygon) {
    if (!polygon) {
        fprintf(stderr, "Warning: gdstk_polygon_get_repetition_rows received null polygon parameter\n");
        return 0;
    }
    return polygon->polygon.repetition.rows;
}

void gdstk_polygon_get_repetition_spacing(const GDSTK_Polygon* polygon, GDSTK_Vec2* spacing) {
    if (!polygon) {
        fprintf(stderr, "Warning: gdstk_polygon_get_repetition_spacing received null polygon parameter\n");
        return;
    }
    if (!spacing) {
        fprintf(stderr, "Warning: gdstk_polygon_get_repetition_spacing received null spacing parameter\n");
        return;
    }
    spacing->x = polygon->polygon.repetition.spacing.x;
    spacing->y = polygon->polygon.repetition.spacing.y;
}

void gdstk_polygon_get_repetition_v1(const GDSTK_Polygon* polygon, GDSTK_Vec2* v1) {
    if (!polygon) {
        fprintf(stderr, "Warning: gdstk_polygon_get_repetition_v1 received null polygon parameter\n");
        return;
    }
    if (!v1) {
        fprintf(stderr, "Warning: gdstk_polygon_get_repetition_v1 received null v1 parameter\n");
        return;
    }
    v1->x = polygon->polygon.repetition.v1.x;
    v1->y = polygon->polygon.repetition.v1.y;
}

void gdstk_polygon_get_repetition_v2(const GDSTK_Polygon* polygon, GDSTK_Vec2* v2) {
    if (!polygon) {
        fprintf(stderr, "Warning: gdstk_polygon_get_repetition_v2 received null polygon parameter\n");
        return;
    }
    if (!v2) {
        fprintf(stderr, "Warning: gdstk_polygon_get_repetition_v2 received null v2 parameter\n");
        return;
    }
    v2->x = polygon->polygon.repetition.v2.x;
    v2->y = polygon->polygon.repetition.v2.y;
}

uint64_t gdstk_polygon_get_repetition_offsets_count(const GDSTK_Polygon* polygon) {
    if (!polygon) {
        fprintf(stderr, "Warning: gdstk_polygon_get_repetition_offsets_count received null polygon parameter\n");
        return 0;
    }
    return polygon->polygon.repetition.offsets.count;
}

void gdstk_polygon_get_repetition_offsets(const GDSTK_Polygon* polygon, GDSTK_Vec2* offsets, uint64_t count) {
    if (!polygon) {
        fprintf(stderr, "Warning: gdstk_polygon_get_repetition_offsets received null polygon parameter\n");
        return;
    }
    if (!offsets) {
        fprintf(stderr, "Warning: gdstk_polygon_get_repetition_offsets received null offsets parameter\n");
        return;
    }
    uint64_t n = count < polygon->polygon.repetition.offsets.count ? count : polygon->polygon.repetition.offsets.count;
    for (uint64_t i = 0; i < n; i++) {
        offsets[i].x = polygon->polygon.repetition.offsets[i].x;
        offsets[i].y = polygon->polygon.repetition.offsets[i].y;
    }
}

uint64_t gdstk_polygon_get_repetition_coords_count(const GDSTK_Polygon* polygon) {
    if (!polygon) {
        fprintf(stderr, "Warning: gdstk_polygon_get_repetition_coords_count received null polygon parameter\n");
        return 0;
    }
    return polygon->polygon.repetition.coords.count;
}

void gdstk_polygon_get_repetition_coords(const GDSTK_Polygon* polygon, double* coords, uint64_t count) {
    if (!polygon) {
        fprintf(stderr, "Warning: gdstk_polygon_get_repetition_coords received null polygon parameter\n");
        return;
    }
    if (!coords) {
        fprintf(stderr, "Warning: gdstk_polygon_get_repetition_coords received null coords parameter\n");
        return;
    }
    uint64_t n = count < polygon->polygon.repetition.coords.count ? count : polygon->polygon.repetition.coords.count;
    for (uint64_t i = 0; i < n; i++) {
        coords[i] = polygon->polygon.repetition.coords[i];
    }
}

uint64_t gdstk_polygon_repetition_get_count(const GDSTK_Polygon* polygon) {
    if (!polygon) {
        fprintf(stderr, "Warning: gdstk_polygon_repetition_get_count received null polygon parameter\n");
        return 0;
    }
    return polygon->polygon.repetition.get_count();
}

// Property getters
GDSTK_PropertyValue* gdstk_polygon_get_property(const GDSTK_Polygon* polygon, const char* name) {
    if (!polygon) {
        fprintf(stderr, "Warning: gdstk_polygon_get_property received null polygon parameter\n");
        return nullptr;
    }
    if (!name) {
        fprintf(stderr, "Warning: gdstk_polygon_get_property received null name parameter\n");
        return nullptr;
    }
    gdstk::PropertyValue* value = get_property(polygon->polygon.properties, name);
    if (!value) {
        return nullptr;
    }
    auto* wrapper = new GDSTK_PropertyValue;
    wrapper->value = value;
    return wrapper;
}

GDSTK_PropertyValue* gdstk_polygon_get_gds_property(const GDSTK_Polygon* polygon, uint16_t attribute) {
    if (!polygon) {
        fprintf(stderr, "Warning: gdstk_polygon_get_gds_property received null polygon parameter\n");
        return nullptr;
    }
    gdstk::PropertyValue* value = get_gds_property(polygon->polygon.properties, attribute);
    if (!value) {
        return nullptr;
    }
    auto* wrapper = new GDSTK_PropertyValue;
    wrapper->value = value;
    return wrapper;
}

// Property value getters
GDSTK_PropertyType gdstk_property_value_get_type(const GDSTK_PropertyValue* property) {
    if (!property || !property->value) {
        fprintf(stderr, "Warning: gdstk_property_value_get_type received null property parameter\n");
        return GDSTK_PropertyType_UnsignedInteger;
    }
    switch (property->value->type) {
        case PropertyType::UnsignedInteger:
            return GDSTK_PropertyType_UnsignedInteger;
        case PropertyType::Integer:
            return GDSTK_PropertyType_Integer;
        case PropertyType::Real:
            return GDSTK_PropertyType_Real;
        case PropertyType::String:
            return GDSTK_PropertyType_String;
        default:
            return GDSTK_PropertyType_UnsignedInteger;
    }
}

uint64_t gdstk_property_value_get_unsigned_integer(const GDSTK_PropertyValue* property) {
    if (!property || !property->value) {
        fprintf(stderr, "Warning: gdstk_property_value_get_unsigned_integer received null property parameter\n");
        return 0;
    }
    if (property->value->type != PropertyType::UnsignedInteger) {
        fprintf(stderr, "Warning: gdstk_property_value_get_unsigned_integer called on non-unsigned-integer property\n");
        return 0;
    }
    return property->value->unsigned_integer;
}

int64_t gdstk_property_value_get_integer(const GDSTK_PropertyValue* property) {
    if (!property || !property->value) {
        fprintf(stderr, "Warning: gdstk_property_value_get_integer received null property parameter\n");
        return 0;
    }
    if (property->value->type != PropertyType::Integer) {
        fprintf(stderr, "Warning: gdstk_property_value_get_integer called on non-integer property\n");
        return 0;
    }
    return property->value->integer;
}

double gdstk_property_value_get_real(const GDSTK_PropertyValue* property) {
    if (!property || !property->value) {
        fprintf(stderr, "Warning: gdstk_property_value_get_real received null property parameter\n");
        return 0.0;
    }
    if (property->value->type != PropertyType::Real) {
        fprintf(stderr, "Warning: gdstk_property_value_get_real called on non-real property\n");
        return 0.0;
    }
    return property->value->real;
}

uint64_t gdstk_property_value_get_string_length(const GDSTK_PropertyValue* property) {
    if (!property || !property->value) {
        fprintf(stderr, "Warning: gdstk_property_value_get_string_length received null property parameter\n");
        return 0;
    }
    if (property->value->type != PropertyType::String) {
        fprintf(stderr, "Warning: gdstk_property_value_get_string_length called on non-string property\n");
        return 0;
    }
    return property->value->count;
}

void gdstk_property_value_get_string(const GDSTK_PropertyValue* property, char* buffer, uint64_t buffer_size) {
    if (!property || !property->value) {
        fprintf(stderr, "Warning: gdstk_property_value_get_string received null property parameter\n");
        return;
    }
    if (!buffer) {
        fprintf(stderr, "Warning: gdstk_property_value_get_string received null buffer parameter\n");
        return;
    }
    if (property->value->type != PropertyType::String) {
        fprintf(stderr, "Warning: gdstk_property_value_get_string called on non-string property\n");
        return;
    }
    uint64_t copy_size = buffer_size < property->value->count ? buffer_size : property->value->count;
    memcpy(buffer, property->value->bytes, copy_size);
    if (buffer_size > copy_size) {
        buffer[copy_size] = '\0';
    }
}

GDSTK_PropertyValue* gdstk_property_value_get_next(const GDSTK_PropertyValue* property) {
    if (!property || !property->value) {
        fprintf(stderr, "Warning: gdstk_property_value_get_next received null property parameter\n");
        return nullptr;
    }
    if (!property->value->next) {
        return nullptr;
    }
    auto* wrapper = new GDSTK_PropertyValue;
    wrapper->value = property->value->next;
    return wrapper;
}

void gdstk_property_value_free(GDSTK_PropertyValue* property) {
    if (!property) {
        fprintf(stderr, "Warning: gdstk_property_value_free received null property parameter\n");
        return;
    }
    delete property;
}

// Constructor and destructor
GDSTK_Polygon* gdstk_polygon_create(int unused) {
    auto* wrapper = new GDSTK_Polygon;
    return wrapper;
}

void gdstk_polygon_free(GDSTK_Polygon* polygon) {
    if (!polygon) {
        fprintf(stderr, "Warning: gdstk_polygon_free received null polygon parameter\n");
        return;
    }
    polygon->polygon.clear();
    delete polygon;
}

void gdstk_polygon_clear(GDSTK_Polygon* polygon) {
    if (!polygon) {
        fprintf(stderr, "Warning: gdstk_polygon_clear received null polygon parameter\n");
        return;
    }
    polygon->polygon.clear();
}

void gdstk_polygon_copy_from(GDSTK_Polygon* dst, const GDSTK_Polygon* src) {
    if (!dst) {
        fprintf(stderr, "Warning: gdstk_polygon_copy_from received null destination parameter\n");
        return;
    }
    if (!src) {
        fprintf(stderr, "Warning: gdstk_polygon_copy_from received null source parameter\n");
        return;
    }
    dst->polygon.copy_from(src->polygon);
}

// Basic properties and methods
double gdstk_polygon_area(const GDSTK_Polygon* polygon) {
    if (!polygon) {
        fprintf(stderr, "Warning: gdstk_polygon_area received null polygon parameter\n");
    }
    return polygon ? polygon->polygon.area() : 0.0;
}

double gdstk_polygon_signed_area(const GDSTK_Polygon* polygon) {
    if (!polygon) {
        fprintf(stderr, "Warning: gdstk_polygon_signed_area received null polygon parameter\n");
    }
    return polygon ? polygon->polygon.signed_area() : 0.0;
}

double gdstk_polygon_perimeter(const GDSTK_Polygon* polygon) {
    if (!polygon) {
        fprintf(stderr, "Warning: gdstk_polygon_perimeter received null polygon parameter\n");
    }
    return polygon ? polygon->polygon.perimeter() : 0.0;
}

// Point containment
int gdstk_polygon_contain(const GDSTK_Polygon* polygon, const GDSTK_Vec2* point) {
    if (!polygon) {
        fprintf(stderr, "Warning: gdstk_polygon_contain received null polygon parameter\n");
        return 0;
    }
    if (!point) {
        fprintf(stderr, "Warning: gdstk_polygon_contain received null point parameter\n");
        return 0;
    }
    Vec2 p = {point->x, point->y};
    return polygon->polygon.contain(p) ? 1 : 0;
}

int gdstk_polygon_contain_all(const GDSTK_Polygon* polygon, const GDSTK_Vec2* points, uint64_t count) {
    if (!polygon) {
        fprintf(stderr, "Warning: gdstk_polygon_contain_all received null polygon parameter\n");
        return 0;
    }
    if (!points) {
        fprintf(stderr, "Warning: gdstk_polygon_contain_all received null points parameter\n");
        return 0;
    }
    Array<Vec2> pts;
    pts.ensure_slots(count);
    for (uint64_t i = 0; i < count; i++) {
        pts.append({points[i].x, points[i].y});
    }
    return polygon->polygon.contain_all(pts) ? 1 : 0;
}

int gdstk_polygon_contain_any(const GDSTK_Polygon* polygon, const GDSTK_Vec2* points, uint64_t count) {
    if (!polygon) {
        fprintf(stderr, "Warning: gdstk_polygon_contain_any received null polygon parameter\n");
        return 0;
    }
    if (!points) {
        fprintf(stderr, "Warning: gdstk_polygon_contain_any received null points parameter\n");
        return 0;
    }
    Array<Vec2> pts;
    pts.ensure_slots(count);
    for (uint64_t i = 0; i < count; i++) {
        pts.append({points[i].x, points[i].y});
    }
    return polygon->polygon.contain_any(pts) ? 1 : 0;
}

// Bounding box
void gdstk_polygon_bounding_box(const GDSTK_Polygon* polygon, GDSTK_Vec2* min, GDSTK_Vec2* max) {
    if (!polygon) {
        fprintf(stderr, "Warning: gdstk_polygon_bounding_box received null polygon parameter\n");
        return;
    }
    if (!min || !max) {
        fprintf(stderr, "Warning: gdstk_polygon_bounding_box received null min/max parameter\n");
        return;
    }
    Vec2 vmin, vmax;
    polygon->polygon.bounding_box(vmin, vmax);
    min->x = vmin.x;
    min->y = vmin.y;
    max->x = vmax.x;
    max->y = vmax.y;
}

// Transformations
void gdstk_polygon_translate(GDSTK_Polygon* polygon, const GDSTK_Vec2* v) {
    if (!polygon) {
        fprintf(stderr, "Warning: gdstk_polygon_translate received null polygon parameter\n");
        return;
    }
    if (!v) {
        fprintf(stderr, "Warning: gdstk_polygon_translate received null vector parameter\n");
        return;
    }
    polygon->polygon.translate({v->x, v->y});
}

void gdstk_polygon_scale(GDSTK_Polygon* polygon, const GDSTK_Vec2* scale, const GDSTK_Vec2* center) {
    if (!polygon) {
        fprintf(stderr, "Warning: gdstk_polygon_scale received null polygon parameter\n");
        return;
    }
    if (!scale) {
        fprintf(stderr, "Warning: gdstk_polygon_scale received null scale parameter\n");
        return;
    }
    if (!center) {
        fprintf(stderr, "Warning: gdstk_polygon_scale received null center parameter\n");
        return;
    }
    polygon->polygon.scale({scale->x, scale->y}, {center->x, center->y});
}

void gdstk_polygon_mirror(GDSTK_Polygon* polygon, const GDSTK_Vec2* p0, const GDSTK_Vec2* p1) {
    if (!polygon) {
        fprintf(stderr, "Warning: gdstk_polygon_mirror received null polygon parameter\n");
        return;
    }
    if (!p0) {
        fprintf(stderr, "Warning: gdstk_polygon_mirror received null p0 parameter\n");
        return;
    }
    if (!p1) {
        fprintf(stderr, "Warning: gdstk_polygon_mirror received null p1 parameter\n");
        return;
    }
    polygon->polygon.mirror({p0->x, p0->y}, {p1->x, p1->y});
}

void gdstk_polygon_rotate(GDSTK_Polygon* polygon, double angle, const GDSTK_Vec2* center) {
    if (!polygon) {
        fprintf(stderr, "Warning: gdstk_polygon_rotate received null polygon parameter\n");
        return;
    }
    if (!center) {
        fprintf(stderr, "Warning: gdstk_polygon_rotate received null center parameter\n");
        return;
    }
    polygon->polygon.rotate(angle, {center->x, center->y});
}

void gdstk_polygon_transform(GDSTK_Polygon* polygon, double magnification, int x_reflection, 
                           double rotation, const GDSTK_Vec2* origin) {
    if (!polygon) {
        fprintf(stderr, "Warning: gdstk_polygon_transform received null polygon parameter\n");
        return;
    }
    if (!origin) {
        fprintf(stderr, "Warning: gdstk_polygon_transform received null origin parameter\n");
        return;
    }
    polygon->polygon.transform(magnification, x_reflection != 0, rotation, {origin->x, origin->y});
}

// Advanced operations
void gdstk_polygon_fillet(GDSTK_Polygon* polygon, const double* radii, uint64_t radii_count, double tolerance) {
    if (!polygon) {
        fprintf(stderr, "Warning: gdstk_polygon_fillet received null polygon parameter\n");
        return;
    }
    if (!radii) {
        fprintf(stderr, "Warning: gdstk_polygon_fillet received null radii parameter\n");
        return;
    }
    Array<double> rad;
    rad.ensure_slots(radii_count);
    for (uint64_t i = 0; i < radii_count; i++) {
        rad.append(radii[i]);
    }
    polygon->polygon.fillet(rad, tolerance);
}

void gdstk_polygon_fracture(const GDSTK_Polygon* polygon, uint64_t max_points, double precision, 
                          GDSTK_Array result) {
    if (!polygon) {
        fprintf(stderr, "Warning: gdstk_polygon_fracture received null polygon parameter\n");
        return;
    }
    if (!result.array) {
        fprintf(stderr, "Warning: gdstk_polygon_fracture received null result parameter\n");
        return;
    }
    polygon->polygon.fracture(max_points, precision, *reinterpret_cast<Array<Polygon*>*>(result.array));
}

void gdstk_polygon_apply_repetition(GDSTK_Polygon* polygon, GDSTK_Array result) {
    if (!polygon) {
        fprintf(stderr, "Warning: gdstk_polygon_apply_repetition received null polygon parameter\n");
        return;
    }
    if (!result.array) {
        fprintf(stderr, "Warning: gdstk_polygon_apply_repetition received null result parameter\n");
        return;
    }
    polygon->polygon.apply_repetition(*reinterpret_cast<Array<Polygon*>*>(result.array));
}

// Factory functions for creating specific polygon shapes
GDSTK_Polygon* gdstk_polygon_rectangle(const GDSTK_Vec2* corner1, const GDSTK_Vec2* corner2, Tag tag) {
    if (!corner1) {
        fprintf(stderr, "Warning: gdstk_polygon_rectangle received null corner1 parameter\n");
        return nullptr;
    }
    if (!corner2) {
        fprintf(stderr, "Warning: gdstk_polygon_rectangle received null corner2 parameter\n");
        return nullptr;
    }
    auto* wrapper = new GDSTK_Polygon;
    wrapper->polygon = rectangle({corner1->x, corner1->y}, {corner2->x, corner2->y}, tag);
    return wrapper;
}

GDSTK_Polygon* gdstk_polygon_cross(const GDSTK_Vec2* center, double full_size, double arm_width, Tag tag) {
    if (!center) {
        fprintf(stderr, "Warning: gdstk_polygon_cross received null center parameter\n");
        return nullptr;
    }
    auto* wrapper = new GDSTK_Polygon;
    wrapper->polygon = cross({center->x, center->y}, full_size, arm_width, tag);
    return wrapper;
}

GDSTK_Polygon* gdstk_polygon_regular(const GDSTK_Vec2* center, double side_length, uint64_t sides, 
                                   double rotation, Tag tag) {
    if (!center) {
        fprintf(stderr, "Warning: gdstk_polygon_regular received null center parameter\n");
        return nullptr;
    }
    auto* wrapper = new GDSTK_Polygon;
    wrapper->polygon = regular_polygon({center->x, center->y}, side_length, sides, rotation, tag);
    return wrapper;
}

GDSTK_Polygon* gdstk_polygon_ellipse(const GDSTK_Vec2* center, double radius_x, double radius_y,
                                    double inner_radius_x, double inner_radius_y,
                                    double initial_angle, double final_angle,
                                    double tolerance, Tag tag) {
    if (!center) {
        fprintf(stderr, "Warning: gdstk_polygon_ellipse received null center parameter\n");
        return nullptr;
    }
    auto* wrapper = new GDSTK_Polygon;
    wrapper->polygon = ellipse({center->x, center->y}, radius_x, radius_y,
                             inner_radius_x, inner_radius_y,
                             initial_angle, final_angle, tolerance, tag);
    return wrapper;
}

GDSTK_Polygon* gdstk_polygon_racetrack(const GDSTK_Vec2* center, double straight_length,
                                      double radius, double inner_radius,
                                      int vertical, double tolerance, Tag tag) {
    if (!center) {
        fprintf(stderr, "Warning: gdstk_polygon_racetrack received null center parameter\n");
        return nullptr;
    }
    auto* wrapper = new GDSTK_Polygon;
    wrapper->polygon = racetrack({center->x, center->y}, straight_length,
                               radius, inner_radius, vertical != 0,
                               tolerance, tag);
    return wrapper;
}

// Text to polygon conversion
void gdstk_polygon_text(const char* s, double size, const GDSTK_Vec2* position,
                       int vertical, Tag tag, struct GDSTK_Array* result) {
    if (!s) {
        fprintf(stderr, "Warning: gdstk_polygon_text received null text parameter\n");
        return;
    }
    if (!position) {
        fprintf(stderr, "Warning: gdstk_polygon_text received null position parameter\n");
        return;
    }
    if (!result) {
        fprintf(stderr, "Warning: gdstk_polygon_text received null result parameter\n");
        return;
    }
    text(s, size, {position->x, position->y}, vertical != 0, tag, *reinterpret_cast<Array<Polygon*>*>(result->array));
}

// Contour generation
int gdstk_polygon_contour(const double* data, uint64_t rows, uint64_t cols,
                         double level, double scaling, struct GDSTK_Array* result) {
    if (!data) {
        fprintf(stderr, "Warning: gdstk_polygon_contour received null data parameter\n");
        return -1;
    }
    if (!result) {
        fprintf(stderr, "Warning: gdstk_polygon_contour received null result parameter\n");
        return -1;
    }
    return contour(data, rows, cols, level, scaling, *reinterpret_cast<Array<Polygon*>*>(result->array)) == ErrorCode::NoError ? 0 : -1;
}

// Point containment for multiple polygons
void gdstk_polygon_inside(const GDSTK_Vec2* points, uint64_t point_count,
                         const GDSTK_Polygon** polygons, uint64_t polygon_count,
                         int* result) {
    if (!points) {
        fprintf(stderr, "Warning: gdstk_polygon_inside received null points parameter\n");
        return;
    }
    if (!polygons) {
        fprintf(stderr, "Warning: gdstk_polygon_inside received null polygons parameter\n");
        return;
    }
    if (!result) {
        fprintf(stderr, "Warning: gdstk_polygon_inside received null result parameter\n");
        return;
    }
    
    Array<Vec2> pts;
    pts.ensure_slots(point_count);
    for (uint64_t i = 0; i < point_count; i++) {
        pts.append({points[i].x, points[i].y});
    }
    
    Array<Polygon*> poly_ptrs;
    poly_ptrs.ensure_slots(polygon_count);
    for (uint64_t i = 0; i < polygon_count; i++) {
        if (polygons[i]) {
            poly_ptrs.append(const_cast<Polygon*>(&polygons[i]->polygon));
        }
    }
    
    bool* temp = new bool[point_count];
    inside(pts, poly_ptrs, temp);
    for (uint64_t i = 0; i < point_count; i++) {
        result[i] = temp[i] ? 1 : 0;
    }
    delete[] temp;
}

int gdstk_polygon_all_inside(const GDSTK_Vec2* points, uint64_t point_count,
                            const GDSTK_Polygon** polygons, uint64_t polygon_count) {
    if (!points) {
        fprintf(stderr, "Warning: gdstk_polygon_all_inside received null points parameter\n");
        return 0;
    }
    if (!polygons) {
        fprintf(stderr, "Warning: gdstk_polygon_all_inside received null polygons parameter\n");
        return 0;
    }
    
    Array<Vec2> pts;
    pts.ensure_slots(point_count);
    for (uint64_t i = 0; i < point_count; i++) {
        pts.append({points[i].x, points[i].y});
    }
    
    Array<Polygon*> poly_ptrs;
    poly_ptrs.ensure_slots(polygon_count);
    for (uint64_t i = 0; i < polygon_count; i++) {
        if (polygons[i]) {
            poly_ptrs.append(const_cast<Polygon*>(&polygons[i]->polygon));
        }
    }
    
    return all_inside(pts, poly_ptrs) ? 1 : 0;
}

int gdstk_polygon_any_inside(const GDSTK_Vec2* points, uint64_t point_count,
                            const GDSTK_Polygon** polygons, uint64_t polygon_count) {
    if (!points) {
        fprintf(stderr, "Warning: gdstk_polygon_any_inside received null points parameter\n");
        return 0;
    }
    if (!polygons) {
        fprintf(stderr, "Warning: gdstk_polygon_any_inside received null polygons parameter\n");
        return 0;
    }
    
    Array<Vec2> pts;
    pts.ensure_slots(point_count);
    for (uint64_t i = 0; i < point_count; i++) {
        pts.append({points[i].x, points[i].y});
    }
    
    Array<Polygon*> poly_ptrs;
    poly_ptrs.ensure_slots(polygon_count);
    for (uint64_t i = 0; i < polygon_count; i++) {
        if (polygons[i]) {
            poly_ptrs.append(const_cast<Polygon*>(&polygons[i]->polygon));
        }
    }
    
    return any_inside(pts, poly_ptrs) ? 1 : 0;
}

} // extern "C"