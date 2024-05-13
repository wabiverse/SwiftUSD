fn main() {
  let mesh_type: u32 = 1;

  println!("rust main: will convert a value of {} to a Ptex MeshType.", mesh_type);

  println!("converting to Ptex.MeshType in swift...");

  let mesh = ffi::Ptex_MeshType(mesh_type);

  println!("swift sent back: {}", mesh);
  println!("program successfully completed.");
}

#[swift_bridge::bridge]
mod ffi {
  extern "Swift" {
      fn Ptex_MeshType(value: u32) -> u32;
  }
}
