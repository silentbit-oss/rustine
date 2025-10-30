use crate::*;
use rand::Rng;

pub fn kmRay3Fill(ray: &mut KmRay3, px: f32, py: f32, pz: f32, vx: f32, vy: f32, vz: f32) -> &mut KmRay3 {
    ray.start.x = px;
    ray.start.y = py;
    ray.start.z = pz;
    ray.dir.x = vx;
    ray.dir.y = vy;
    ray.dir.z = vz;
    ray
}
pub fn kmRay3FromPointAndDirection<'a>(
    ray: Option<&'a mut KmRay3>,
    point: Option<&'a KmVec3>,
    direction: Option<&'a KmVec3>,
) -> Option<&'a mut KmRay3> {
    let ray = ray?;
    {
        let start = &mut ray.start;
        kmVec3Assign(Some(start), point);
    }
    {
        let dir = &mut ray.dir;
        kmVec3Assign(Some(dir), direction);
    }
    Some(ray)
}

pub fn kmRay3IntersectPlane(pOut: &mut KmVec3, ray: &KmRay3, plane: &KmPlane) -> u8 {
    let d = (plane.a * ray.dir.x) + (plane.b * ray.dir.y) + (plane.c * ray.dir.z);
    if d == 0.0 {
        return 0;
    }

    let t = -((plane.a * ray.start.x) + (plane.b * ray.start.y) + (plane.c * ray.start.z) + plane.d) / d;
    if t < 0.0 {
        return 0;
    }

    let mut scaled_dir = KmVec3 { x: 0.0, y: 0.0, z: 0.0 };
    kmVec3Scale(&mut scaled_dir, &ray.dir, t);
    kmVec3Add(pOut, &ray.start, &scaled_dir);
    
    1
}
