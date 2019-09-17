Library ieee;
Use ieee.std_logic_1164.all;

entity NineCPM is
port (
      a, b, c, d : in std_logic;
      x, y, z, k : out std_logic);
end entity;

architecture rtl of NineCPM is
begin

   x <= (not a) and (not b) and (not c);
   y <= ((not c) and (b)) or ((c) and (not b));
   Z <= c;
   k <= (not d);
   
end architecture;