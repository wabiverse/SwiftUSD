fn main() {
  let start_num = 100;

  println!("The Rust starting number is {}.", start_num);

  let num = ffi::AlignMemorySize(start_num);

  println!("Printing the number from Rust...");
  println!("The number is now {}.", num)
}

#[swift_bridge::bridge]
mod ffi {
  extern "Swift" {
      fn AlignMemorySize(byteCount: i64) -> i64;
  }
}
