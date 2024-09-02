/* Write Verilog code to convert 4-bit gray code to binary code 
using 8:1 multiplexers. */
module Mux8to1 (s, w, f);
input [0:2] s;
input [0:7] w;
output f;
reg g;
always@(*)
begin
case(s)
  3'b000:g=w[0];
  3'b001:g=w[1];
  3'b010:g=w[2];
  3'b011:g=w[3];
  3'b100:g=w[4];
  3'b101:g=w[5];
  3'b110:g=w[6];
  3'b111:g=w[7];
endcase
end
assign f = g;
endmodule

module GrayToBin_Mux8to1 (G, B);
input [3:0] G;
output [3:0] B;
assign G[3] = B[3];
//assign G[2] = 
//assign G[1] = 
//assign G[0] = 
endmodule
