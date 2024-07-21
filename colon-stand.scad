H = 21;
Q = 1.2;
D = 1;
module j() {
    cylinder(h=100, d=D, $fn=20);
    translate([0,0,H-Q]) cylinder(5,0,5,$fn=20);
    cylinder(Q,Q,0,$fn=20);
}

difference() {
  hull() {
    translate([6.5, 0]) cylinder(h=H, d=4, $fn=50);
    translate([-6.5, 0]) cylinder(h=H, d=4, $fn=50);
  }
  translate([6.5, 0]) j();
  translate([-6.5, 0]) j();
  translate([3.5, 0]) j();
  translate([-3.5, 0]) j();

}