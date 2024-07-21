PCB_THICKNESS = 1.6;
EDGE_LENGTH = 54;
WRAPAROUND = 2;

module thingie() {
  translate([1, 0, 0]) {
    difference() {
      cube([
        EDGE_LENGTH + 2 * WRAPAROUND,
        EDGE_LENGTH + 2 * WRAPAROUND*2 + PCB_THICKNESS,
        9]);
      translate([EDGE_LENGTH+17+5+3, EDGE_LENGTH+5+5]) {
        cylinder(10, EDGE_LENGTH+5, EDGE_LENGTH+5, $fn=500);
      };

      translate([-141,73]) {
        cylinder(10, 155, 155, $fn=500);
      };


      translate([WRAPAROUND, WRAPAROUND*3,1])  {
        translate([14, PCB_THICKNESS,0])  {
          cube([PCB_THICKNESS,EDGE_LENGTH,20]);
        }
        cube([EDGE_LENGTH,PCB_THICKNESS,20]);
      }
    }
  }
}

thingie();
mirror([1,0,0]) {
  thingie();
}
