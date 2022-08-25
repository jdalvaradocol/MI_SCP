----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 20.08.2022 08:43:25
-- Design Name: 
-- Module Name: interruptor_tb - Behavioral
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

entity interruptor_tb is
--  Port ( );
end interruptor_tb;

architecture Behavioral of interruptor_tb is

signal clk_tb : std_logic:='0';
signal led_tb : std_logic:='0';
signal  sw_tb : std_logic:='0';

signal contador_tb : std_logic_vector(3 downto 0); 

begin

    clk_tb <= not clk_tb after 1ns;
    
    sw_tb <= '1' after  5ns, '0' after 6ns,    -- Genera un pulso de 1 ns en 5ns
             '1' after 20ns, '0' after 21ns,   -- Genera un pulso de 1 ns en 20ns
             '1' after 25ns, '0' after 26ns;   -- Genera un pulso de 1 ns en 25ns

    MSF: entity work.interruptor port map
    (
             clk_i => clk_tb,
              sw_i =>  sw_tb,
             led_o => led_tb,
        contador_o => contador_tb    
    );

--    MSF: entity work.interruptor port map ( clk_tb, sw_tb, led_tb,  contador_tb );


end Behavioral;
