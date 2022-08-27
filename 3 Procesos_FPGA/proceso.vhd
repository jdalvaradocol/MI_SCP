----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 20.08.2022 11:30:48
-- Design Name: 
-- Module Name: proceso - Behavioral
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

entity proceso is
    Port ( clk_i : in STD_LOGIC;
           sw_i : in STD_LOGIC_VECTOR (1 downto 0);
           salida_o : out STD_LOGIC_VECTOR (3 downto 0));
end proceso;

architecture Behavioral of proceso is

type estado_type is (E1, E2, E3, E4);
signal estado : estado_type:= E1; 
signal salida : std_logic_vector(3 downto 0); 

begin

    process(clk_i, sw_i)
    
    begin
    
        if rising_edge(clk_i) then
        
            if estado = E1 then
            
                if (sw_i = "00") then   
                    estado <= E2; 
                elsif (sw_i = "01") then   
                    estado <= E4; 
                elsif (sw_i = "10") or (sw_i = "11") then  
                    estado <= E1; 
                end if;
                
                salida <= "0001";
                
            elsif estado = E2 then
            
                if (sw_i = "00") then   
                    estado <= E3; 
                elsif (sw_i = "01") then   
                    estado <= E1; 
                elsif (sw_i = "10") or (sw_i = "11") then  
                    estado <= E2; 
                end if;
                
                salida <= "0010";
           
            elsif estado = E3 then
            
                if (sw_i = "00") then   
                    estado <= E4; 
                elsif (sw_i = "01") then   
                    estado <= E2; 
                elsif (sw_i = "10") or (sw_i = "11") then  
                    estado <= E3; 
                end if;
                
                salida <= "0100";
        
            elsif estado = E4 then
            
                if (sw_i = "00") then   
                    estado <= E1; 
                elsif (sw_i = "01") then   
                    estado <= E3; 
                elsif (sw_i = "10") or (sw_i = "11") then  
                    estado <= E4; 
                end if;
                
                salida <= "1000";
    
            end if;

       end if;
    
    end process;

    salida_o <= salida;

end Behavioral;
