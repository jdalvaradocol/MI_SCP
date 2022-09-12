----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 25.08.2022 19:15:28
-- Design Name: 
-- Module Name: principal - Behavioral
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

entity principal is
    Port (      clk_i : in STD_LOGIC;
                 sw_i : in STD_LOGIC;
                clk_o : out STD_LOGIC;
                led_o : out STD_LOGIC;
           Contador_o : out STD_LOGIC_VECTOR (3 downto 0));
end principal;

architecture Behavioral of principal is

signal clk : std_logic := '0';

begin

    clk_ticks: entity work.clk_div generic map
    (
        TICKS => 62e6
    )
    port map
    (
        clk_i => clk_i,
        clk_o => clk    
    );
    
    sw: entity work.interruptor port map
    (
        clk_i       => clk,
        sw_i        => sw_i,
        led_o       => led_o,
        contador_o  => contador_o
    );
    
    clk_o <= clk;
    
end Behavioral;
