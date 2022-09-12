----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 09.09.2022 12:27:38
-- Design Name: 
-- Module Name: modelo_asin_tb - Behavioral
-- Project Name: 
-- Target Devices: 
-- Tool Versions: 
-- Description: 
-- 
-- Dependencies: 
-- 
-- Revision:
-- Revision 0.01 - File Created
-- Additional Comments:
-- 
----------------------------------------------------------------------------------


library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity modelo_asin_tb is
--  Port ( );
end modelo_asin_tb;

architecture Behavioral of modelo_asin_tb is

signal  input_tb : std_logic:= '0';
signal output_tb : std_logic:= '0';
signal   temp_tb : std_logic:= '0';

begin
    
    input_tb <= not input_tb after 25 ns;
    
    modelo: entity work.modelo_asin port map
    (
         input_i => input_tb,
        output_o => output_tb,
          temp_o => temp_tb
    );


end Behavioral;
