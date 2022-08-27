----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 20.08.2022 11:47:32
-- Design Name: 
-- Module Name: proceso_tb - Behavioral
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

entity proceso_tb is
--  Port ( );
end proceso_tb;

architecture Behavioral of proceso_tb is

signal     clk_tb  : std_logic:= '0';
signal      sw_tb  : std_logic_vector(1 downto 0):= "00";
signal  salida_tb  : std_logic_vector(3 downto 0):= "0000";

begin

    clk_tb <= not clk_tb after 1ns;
    sw_tb  <= "01" after 10ns,"10" after 20ns,"11" after 30ns,"00" after 40ns;

    MEF: entity work.proceso port map
    (
        clk_i => clk_tb,
         sw_i => sw_tb,
     salida_o => salida_tb  
    );

end Behavioral;
