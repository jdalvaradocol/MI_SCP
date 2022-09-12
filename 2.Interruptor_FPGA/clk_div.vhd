----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 25.08.2022 18:59:05
-- Design Name: 
-- Module Name: clk_div - Behavioral
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

entity clk_div is
    generic(
        TICKS : integer := 0  
    );
    Port ( 
        clk_i : in STD_LOGIC;
        clk_o : out STD_LOGIC);
end clk_div;

architecture Behavioral of clk_div is

signal clk : std_logic:='0';
signal div_ticks : integer range 0 to TICKS - 1 := 0;

begin

    process(clk_i)
    begin
        
        if rising_edge(clk_i) then
            
            if div_ticks = (TICKS - 1) then
                
                clk <= not clk;
                
             end if;
            
            div_ticks <= div_ticks + 1;
            
        end if;        
    
        end process;

clk_o <= clk;
    
end Behavioral;
