----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 19.08.2022 21:21:05
-- Design Name: 
-- Module Name: interruptor - Behavioral
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
use IEEE.numeric_std.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity interruptor is
    Port (   clk_i : in STD_LOGIC;
              sw_i : in STD_LOGIC;
             led_o : out STD_LOGIC;
        contador_o : out STD_LOGIC_VECTOR (3 downto 0));
end interruptor;

architecture Behavioral of interruptor is

type state_type is  (Apagado, Encendido);   -- Estado tipo enumerate
signal estado : state_type:= Apagado;       -- Variable de estado 
signal x : integer range 0 to 10 := 0;      -- Variable contador x
signal led : std_logic:='0';

begin

    estado_u:process(clk_i, sw_i)
    
    begin
         
       if(estado = Apagado) and sw_i = '0' then        
            led <= '0';
            x <=0;
        elsif (estado = Encendido) then
               
            led <= '1';
            
            if x < 9 then
                x <= x + 1;
            else
                x<= 0;
            end if;     
    
        end if;
    
    end process;
   
    sw:process(clk_i, sw_i)
    
    begin
    
        if  (estado = Encendido) and x = 9 then 
                estado <= Apagado; 
        elsif rising_edge(sw_i) then  
        
            if (estado = Apagado) then
                estado <= Encendido; 
            elsif (estado = Encendido) then            
                estado <= Apagado;
            end if;
        
        end if;
        
     end process;
   
    contador_o <= std_logic_vector(to_unsigned(x,contador_o'length));
    led_o <= led;

end Behavioral;
