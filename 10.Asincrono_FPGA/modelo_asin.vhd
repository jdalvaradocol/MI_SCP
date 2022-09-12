----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 08.09.2022 19:15:03
-- Design Name: 
-- Module Name: modelo_asin - Behavioral
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

entity modelo_asin is
    Port (   input_i : in STD_LOGIC;
            output_o : out STD_LOGIC;
              temp_o : out STD_LOGIC);
end modelo_asin;

architecture Behavioral of modelo_asin is

type x_type is (CERO, UNO, NULO);
signal x1    : x_type := NULO;
signal x2    : x_type := NULO;

signal temp  : std_logic := '0';
signal selx1 : std_logic_vector (1 downto 0) := "00";
signal selx2 : std_logic_vector (1 downto 0) := "00";

begin

    Ai: process (input_i)
        begin      
            selx1 <= '0' & input_i;
        end process;

    At: process (x1)
        begin
            temp     <= selx1(0);    
            temp_o   <= selx1(0); 
            selx2    <= '0' & selx1(0);
            selx1(1) <= '1'; 
        end process;      

    x1 <= CERO when selx1 = "00" else UNO when selx1 = "01" else NULO;

    Ao: process (x2)
        begin      
            output_o <= temp;
            selx2(1) <= '1';  
        end process;      
  
    x2 <= CERO when selx2 = "00" else UNO when selx2 = "01" else NULO;
            
end Behavioral;
