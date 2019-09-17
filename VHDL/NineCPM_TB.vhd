library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity NineTB is
end entity;


architecture sim of NineTB is
--define Constants

--define Signals
   signal INPUTS    : signed(0 to 3) := "0000";
   signal OUTPUTS   : signed(0 to 3) := "0000";
   
begin
   -- Correspoing Ports 
   i_NineTB : entity work.NineCPM(rtl)
      port map(
   --INPUT a(MSB),b,c,d(LSB)
      a => INPUTS(0),
      b => INPUTS(1),
      c => INPUTS(2),
      d => INPUTS(3),
   --OUTPUT X(MSB),Y,Z,K(LSB)
      x => OUTPUTS(0),
      y => OUTPUTS(1),
      z => OUTPUTS(2),
      k => OUTPUTS(3)   );
   
   process is
      begin
      --Change INPUT from 0000 to 1001 
         for i in 0 to 9 loop
            wait for 100 ns;
            INPUTS <= INPUTS +1 ;   
         end loop;
      --Repeat the same Process
            INPUTS <= "0000";
   end process;
   
end architecture;