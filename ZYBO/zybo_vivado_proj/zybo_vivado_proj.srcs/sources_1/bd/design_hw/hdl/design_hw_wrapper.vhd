--Copyright 1986-2015 Xilinx, Inc. All Rights Reserved.
----------------------------------------------------------------------------------
--Tool Version: Vivado v.2015.4 (win64) Build 1412921 Wed Nov 18 09:43:45 MST 2015
--Date        : Mon Feb 22 22:49:47 2016
--Host        : DESKTOP-567HUN5 running 64-bit major release  (build 9200)
--Command     : generate_target design_hw_wrapper.bd
--Design      : design_hw_wrapper
--Purpose     : IP block netlist
----------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity design_hw_wrapper is
  port (
    DDR_addr : inout STD_LOGIC_VECTOR ( 14 downto 0 );
    DDR_ba : inout STD_LOGIC_VECTOR ( 2 downto 0 );
    DDR_cas_n : inout STD_LOGIC;
    DDR_ck_n : inout STD_LOGIC;
    DDR_ck_p : inout STD_LOGIC;
    DDR_cke : inout STD_LOGIC;
    DDR_cs_n : inout STD_LOGIC;
    DDR_dm : inout STD_LOGIC_VECTOR ( 3 downto 0 );
    DDR_dq : inout STD_LOGIC_VECTOR ( 31 downto 0 );
    DDR_dqs_n : inout STD_LOGIC_VECTOR ( 3 downto 0 );
    DDR_dqs_p : inout STD_LOGIC_VECTOR ( 3 downto 0 );
    DDR_odt : inout STD_LOGIC;
    DDR_ras_n : inout STD_LOGIC;
    DDR_reset_n : inout STD_LOGIC;
    DDR_we_n : inout STD_LOGIC;
    FIXED_IO_ddr_vrn : inout STD_LOGIC;
    FIXED_IO_ddr_vrp : inout STD_LOGIC;
    FIXED_IO_mio : inout STD_LOGIC_VECTOR ( 53 downto 0 );
    FIXED_IO_ps_clk : inout STD_LOGIC;
    FIXED_IO_ps_porb : inout STD_LOGIC;
    FIXED_IO_ps_srstb : inout STD_LOGIC;
    gpio_rtl_0_tri_io : inout STD_LOGIC_VECTOR ( 2 downto 0 );
    gpio_rtl_tri_io : inout STD_LOGIC_VECTOR ( 3 downto 0 );
    spi_rtl_0_io0_io : inout STD_LOGIC;
    spi_rtl_0_io1_io : inout STD_LOGIC;
    spi_rtl_0_sck_io : inout STD_LOGIC;
    spi_rtl_0_ss_io : inout STD_LOGIC_VECTOR ( 0 to 0 );
    spi_rtl_io0_io : inout STD_LOGIC;
    spi_rtl_io1_io : inout STD_LOGIC;
    spi_rtl_sck_io : inout STD_LOGIC;
    spi_rtl_ss_io : inout STD_LOGIC_VECTOR ( 0 to 0 )
  );
end design_hw_wrapper;

architecture STRUCTURE of design_hw_wrapper is
  component design_hw is
  port (
    DDR_cas_n : inout STD_LOGIC;
    DDR_cke : inout STD_LOGIC;
    DDR_ck_n : inout STD_LOGIC;
    DDR_ck_p : inout STD_LOGIC;
    DDR_cs_n : inout STD_LOGIC;
    DDR_reset_n : inout STD_LOGIC;
    DDR_odt : inout STD_LOGIC;
    DDR_ras_n : inout STD_LOGIC;
    DDR_we_n : inout STD_LOGIC;
    DDR_ba : inout STD_LOGIC_VECTOR ( 2 downto 0 );
    DDR_addr : inout STD_LOGIC_VECTOR ( 14 downto 0 );
    DDR_dm : inout STD_LOGIC_VECTOR ( 3 downto 0 );
    DDR_dq : inout STD_LOGIC_VECTOR ( 31 downto 0 );
    DDR_dqs_n : inout STD_LOGIC_VECTOR ( 3 downto 0 );
    DDR_dqs_p : inout STD_LOGIC_VECTOR ( 3 downto 0 );
    FIXED_IO_mio : inout STD_LOGIC_VECTOR ( 53 downto 0 );
    FIXED_IO_ddr_vrn : inout STD_LOGIC;
    FIXED_IO_ddr_vrp : inout STD_LOGIC;
    FIXED_IO_ps_srstb : inout STD_LOGIC;
    FIXED_IO_ps_clk : inout STD_LOGIC;
    FIXED_IO_ps_porb : inout STD_LOGIC;
    gpio_rtl_tri_i : in STD_LOGIC_VECTOR ( 3 downto 0 );
    gpio_rtl_tri_o : out STD_LOGIC_VECTOR ( 3 downto 0 );
    gpio_rtl_tri_t : out STD_LOGIC_VECTOR ( 3 downto 0 );
    spi_rtl_io0_i : in STD_LOGIC;
    spi_rtl_io0_o : out STD_LOGIC;
    spi_rtl_io0_t : out STD_LOGIC;
    spi_rtl_io1_i : in STD_LOGIC;
    spi_rtl_io1_o : out STD_LOGIC;
    spi_rtl_io1_t : out STD_LOGIC;
    spi_rtl_sck_i : in STD_LOGIC;
    spi_rtl_sck_o : out STD_LOGIC;
    spi_rtl_sck_t : out STD_LOGIC;
    spi_rtl_ss_i : in STD_LOGIC_VECTOR ( 0 to 0 );
    spi_rtl_ss_o : out STD_LOGIC_VECTOR ( 0 to 0 );
    spi_rtl_ss_t : out STD_LOGIC;
    spi_rtl_0_io0_i : in STD_LOGIC;
    spi_rtl_0_io0_o : out STD_LOGIC;
    spi_rtl_0_io0_t : out STD_LOGIC;
    spi_rtl_0_io1_i : in STD_LOGIC;
    spi_rtl_0_io1_o : out STD_LOGIC;
    spi_rtl_0_io1_t : out STD_LOGIC;
    spi_rtl_0_sck_i : in STD_LOGIC;
    spi_rtl_0_sck_o : out STD_LOGIC;
    spi_rtl_0_sck_t : out STD_LOGIC;
    spi_rtl_0_ss_i : in STD_LOGIC_VECTOR ( 0 to 0 );
    spi_rtl_0_ss_o : out STD_LOGIC_VECTOR ( 0 to 0 );
    spi_rtl_0_ss_t : out STD_LOGIC;
    gpio_rtl_0_tri_i : in STD_LOGIC_VECTOR ( 2 downto 0 );
    gpio_rtl_0_tri_o : out STD_LOGIC_VECTOR ( 2 downto 0 );
    gpio_rtl_0_tri_t : out STD_LOGIC_VECTOR ( 2 downto 0 )
  );
  end component design_hw;
  component IOBUF is
  port (
    I : in STD_LOGIC;
    O : out STD_LOGIC;
    T : in STD_LOGIC;
    IO : inout STD_LOGIC
  );
  end component IOBUF;
  signal gpio_rtl_0_tri_i_0 : STD_LOGIC_VECTOR ( 0 to 0 );
  signal gpio_rtl_0_tri_i_1 : STD_LOGIC_VECTOR ( 1 to 1 );
  signal gpio_rtl_0_tri_i_2 : STD_LOGIC_VECTOR ( 2 to 2 );
  signal gpio_rtl_0_tri_io_0 : STD_LOGIC_VECTOR ( 0 to 0 );
  signal gpio_rtl_0_tri_io_1 : STD_LOGIC_VECTOR ( 1 to 1 );
  signal gpio_rtl_0_tri_io_2 : STD_LOGIC_VECTOR ( 2 to 2 );
  signal gpio_rtl_0_tri_o_0 : STD_LOGIC_VECTOR ( 0 to 0 );
  signal gpio_rtl_0_tri_o_1 : STD_LOGIC_VECTOR ( 1 to 1 );
  signal gpio_rtl_0_tri_o_2 : STD_LOGIC_VECTOR ( 2 to 2 );
  signal gpio_rtl_0_tri_t_0 : STD_LOGIC_VECTOR ( 0 to 0 );
  signal gpio_rtl_0_tri_t_1 : STD_LOGIC_VECTOR ( 1 to 1 );
  signal gpio_rtl_0_tri_t_2 : STD_LOGIC_VECTOR ( 2 to 2 );
  signal gpio_rtl_tri_i_0 : STD_LOGIC_VECTOR ( 0 to 0 );
  signal gpio_rtl_tri_i_1 : STD_LOGIC_VECTOR ( 1 to 1 );
  signal gpio_rtl_tri_i_2 : STD_LOGIC_VECTOR ( 2 to 2 );
  signal gpio_rtl_tri_i_3 : STD_LOGIC_VECTOR ( 3 to 3 );
  signal gpio_rtl_tri_io_0 : STD_LOGIC_VECTOR ( 0 to 0 );
  signal gpio_rtl_tri_io_1 : STD_LOGIC_VECTOR ( 1 to 1 );
  signal gpio_rtl_tri_io_2 : STD_LOGIC_VECTOR ( 2 to 2 );
  signal gpio_rtl_tri_io_3 : STD_LOGIC_VECTOR ( 3 to 3 );
  signal gpio_rtl_tri_o_0 : STD_LOGIC_VECTOR ( 0 to 0 );
  signal gpio_rtl_tri_o_1 : STD_LOGIC_VECTOR ( 1 to 1 );
  signal gpio_rtl_tri_o_2 : STD_LOGIC_VECTOR ( 2 to 2 );
  signal gpio_rtl_tri_o_3 : STD_LOGIC_VECTOR ( 3 to 3 );
  signal gpio_rtl_tri_t_0 : STD_LOGIC_VECTOR ( 0 to 0 );
  signal gpio_rtl_tri_t_1 : STD_LOGIC_VECTOR ( 1 to 1 );
  signal gpio_rtl_tri_t_2 : STD_LOGIC_VECTOR ( 2 to 2 );
  signal gpio_rtl_tri_t_3 : STD_LOGIC_VECTOR ( 3 to 3 );
  signal spi_rtl_0_io0_i : STD_LOGIC;
  signal spi_rtl_0_io0_o : STD_LOGIC;
  signal spi_rtl_0_io0_t : STD_LOGIC;
  signal spi_rtl_0_io1_i : STD_LOGIC;
  signal spi_rtl_0_io1_o : STD_LOGIC;
  signal spi_rtl_0_io1_t : STD_LOGIC;
  signal spi_rtl_0_sck_i : STD_LOGIC;
  signal spi_rtl_0_sck_o : STD_LOGIC;
  signal spi_rtl_0_sck_t : STD_LOGIC;
  signal spi_rtl_0_ss_i_0 : STD_LOGIC_VECTOR ( 0 to 0 );
  signal spi_rtl_0_ss_io_0 : STD_LOGIC_VECTOR ( 0 to 0 );
  signal spi_rtl_0_ss_o_0 : STD_LOGIC_VECTOR ( 0 to 0 );
  signal spi_rtl_0_ss_t : STD_LOGIC;
  signal spi_rtl_io0_i : STD_LOGIC;
  signal spi_rtl_io0_o : STD_LOGIC;
  signal spi_rtl_io0_t : STD_LOGIC;
  signal spi_rtl_io1_i : STD_LOGIC;
  signal spi_rtl_io1_o : STD_LOGIC;
  signal spi_rtl_io1_t : STD_LOGIC;
  signal spi_rtl_sck_i : STD_LOGIC;
  signal spi_rtl_sck_o : STD_LOGIC;
  signal spi_rtl_sck_t : STD_LOGIC;
  signal spi_rtl_ss_i_0 : STD_LOGIC_VECTOR ( 0 to 0 );
  signal spi_rtl_ss_io_0 : STD_LOGIC_VECTOR ( 0 to 0 );
  signal spi_rtl_ss_o_0 : STD_LOGIC_VECTOR ( 0 to 0 );
  signal spi_rtl_ss_t : STD_LOGIC;
begin
design_hw_i: component design_hw
     port map (
      DDR_addr(14 downto 0) => DDR_addr(14 downto 0),
      DDR_ba(2 downto 0) => DDR_ba(2 downto 0),
      DDR_cas_n => DDR_cas_n,
      DDR_ck_n => DDR_ck_n,
      DDR_ck_p => DDR_ck_p,
      DDR_cke => DDR_cke,
      DDR_cs_n => DDR_cs_n,
      DDR_dm(3 downto 0) => DDR_dm(3 downto 0),
      DDR_dq(31 downto 0) => DDR_dq(31 downto 0),
      DDR_dqs_n(3 downto 0) => DDR_dqs_n(3 downto 0),
      DDR_dqs_p(3 downto 0) => DDR_dqs_p(3 downto 0),
      DDR_odt => DDR_odt,
      DDR_ras_n => DDR_ras_n,
      DDR_reset_n => DDR_reset_n,
      DDR_we_n => DDR_we_n,
      FIXED_IO_ddr_vrn => FIXED_IO_ddr_vrn,
      FIXED_IO_ddr_vrp => FIXED_IO_ddr_vrp,
      FIXED_IO_mio(53 downto 0) => FIXED_IO_mio(53 downto 0),
      FIXED_IO_ps_clk => FIXED_IO_ps_clk,
      FIXED_IO_ps_porb => FIXED_IO_ps_porb,
      FIXED_IO_ps_srstb => FIXED_IO_ps_srstb,
      gpio_rtl_0_tri_i(2) => gpio_rtl_0_tri_i_2(2),
      gpio_rtl_0_tri_i(1) => gpio_rtl_0_tri_i_1(1),
      gpio_rtl_0_tri_i(0) => gpio_rtl_0_tri_i_0(0),
      gpio_rtl_0_tri_o(2) => gpio_rtl_0_tri_o_2(2),
      gpio_rtl_0_tri_o(1) => gpio_rtl_0_tri_o_1(1),
      gpio_rtl_0_tri_o(0) => gpio_rtl_0_tri_o_0(0),
      gpio_rtl_0_tri_t(2) => gpio_rtl_0_tri_t_2(2),
      gpio_rtl_0_tri_t(1) => gpio_rtl_0_tri_t_1(1),
      gpio_rtl_0_tri_t(0) => gpio_rtl_0_tri_t_0(0),
      gpio_rtl_tri_i(3) => gpio_rtl_tri_i_3(3),
      gpio_rtl_tri_i(2) => gpio_rtl_tri_i_2(2),
      gpio_rtl_tri_i(1) => gpio_rtl_tri_i_1(1),
      gpio_rtl_tri_i(0) => gpio_rtl_tri_i_0(0),
      gpio_rtl_tri_o(3) => gpio_rtl_tri_o_3(3),
      gpio_rtl_tri_o(2) => gpio_rtl_tri_o_2(2),
      gpio_rtl_tri_o(1) => gpio_rtl_tri_o_1(1),
      gpio_rtl_tri_o(0) => gpio_rtl_tri_o_0(0),
      gpio_rtl_tri_t(3) => gpio_rtl_tri_t_3(3),
      gpio_rtl_tri_t(2) => gpio_rtl_tri_t_2(2),
      gpio_rtl_tri_t(1) => gpio_rtl_tri_t_1(1),
      gpio_rtl_tri_t(0) => gpio_rtl_tri_t_0(0),
      spi_rtl_0_io0_i => spi_rtl_0_io0_i,
      spi_rtl_0_io0_o => spi_rtl_0_io0_o,
      spi_rtl_0_io0_t => spi_rtl_0_io0_t,
      spi_rtl_0_io1_i => spi_rtl_0_io1_i,
      spi_rtl_0_io1_o => spi_rtl_0_io1_o,
      spi_rtl_0_io1_t => spi_rtl_0_io1_t,
      spi_rtl_0_sck_i => spi_rtl_0_sck_i,
      spi_rtl_0_sck_o => spi_rtl_0_sck_o,
      spi_rtl_0_sck_t => spi_rtl_0_sck_t,
      spi_rtl_0_ss_i(0) => spi_rtl_0_ss_i_0(0),
      spi_rtl_0_ss_o(0) => spi_rtl_0_ss_o_0(0),
      spi_rtl_0_ss_t => spi_rtl_0_ss_t,
      spi_rtl_io0_i => spi_rtl_io0_i,
      spi_rtl_io0_o => spi_rtl_io0_o,
      spi_rtl_io0_t => spi_rtl_io0_t,
      spi_rtl_io1_i => spi_rtl_io1_i,
      spi_rtl_io1_o => spi_rtl_io1_o,
      spi_rtl_io1_t => spi_rtl_io1_t,
      spi_rtl_sck_i => spi_rtl_sck_i,
      spi_rtl_sck_o => spi_rtl_sck_o,
      spi_rtl_sck_t => spi_rtl_sck_t,
      spi_rtl_ss_i(0) => spi_rtl_ss_i_0(0),
      spi_rtl_ss_o(0) => spi_rtl_ss_o_0(0),
      spi_rtl_ss_t => spi_rtl_ss_t
    );
gpio_rtl_0_tri_iobuf_0: component IOBUF
     port map (
      I => gpio_rtl_0_tri_o_0(0),
      IO => gpio_rtl_0_tri_io(0),
      O => gpio_rtl_0_tri_i_0(0),
      T => gpio_rtl_0_tri_t_0(0)
    );
gpio_rtl_0_tri_iobuf_1: component IOBUF
     port map (
      I => gpio_rtl_0_tri_o_1(1),
      IO => gpio_rtl_0_tri_io(1),
      O => gpio_rtl_0_tri_i_1(1),
      T => gpio_rtl_0_tri_t_1(1)
    );
gpio_rtl_0_tri_iobuf_2: component IOBUF
     port map (
      I => gpio_rtl_0_tri_o_2(2),
      IO => gpio_rtl_0_tri_io(2),
      O => gpio_rtl_0_tri_i_2(2),
      T => gpio_rtl_0_tri_t_2(2)
    );
gpio_rtl_tri_iobuf_0: component IOBUF
     port map (
      I => gpio_rtl_tri_o_0(0),
      IO => gpio_rtl_tri_io(0),
      O => gpio_rtl_tri_i_0(0),
      T => gpio_rtl_tri_t_0(0)
    );
gpio_rtl_tri_iobuf_1: component IOBUF
     port map (
      I => gpio_rtl_tri_o_1(1),
      IO => gpio_rtl_tri_io(1),
      O => gpio_rtl_tri_i_1(1),
      T => gpio_rtl_tri_t_1(1)
    );
gpio_rtl_tri_iobuf_2: component IOBUF
     port map (
      I => gpio_rtl_tri_o_2(2),
      IO => gpio_rtl_tri_io(2),
      O => gpio_rtl_tri_i_2(2),
      T => gpio_rtl_tri_t_2(2)
    );
gpio_rtl_tri_iobuf_3: component IOBUF
     port map (
      I => gpio_rtl_tri_o_3(3),
      IO => gpio_rtl_tri_io(3),
      O => gpio_rtl_tri_i_3(3),
      T => gpio_rtl_tri_t_3(3)
    );
spi_rtl_0_io0_iobuf: component IOBUF
     port map (
      I => spi_rtl_0_io0_o,
      IO => spi_rtl_0_io0_io,
      O => spi_rtl_0_io0_i,
      T => spi_rtl_0_io0_t
    );
spi_rtl_0_io1_iobuf: component IOBUF
     port map (
      I => spi_rtl_0_io1_o,
      IO => spi_rtl_0_io1_io,
      O => spi_rtl_0_io1_i,
      T => spi_rtl_0_io1_t
    );
spi_rtl_0_sck_iobuf: component IOBUF
     port map (
      I => spi_rtl_0_sck_o,
      IO => spi_rtl_0_sck_io,
      O => spi_rtl_0_sck_i,
      T => spi_rtl_0_sck_t
    );
spi_rtl_0_ss_iobuf_0: component IOBUF
     port map (
      I => spi_rtl_0_ss_o_0(0),
      IO => spi_rtl_0_ss_io(0),
      O => spi_rtl_0_ss_i_0(0),
      T => spi_rtl_0_ss_t
    );
spi_rtl_io0_iobuf: component IOBUF
     port map (
      I => spi_rtl_io0_o,
      IO => spi_rtl_io0_io,
      O => spi_rtl_io0_i,
      T => spi_rtl_io0_t
    );
spi_rtl_io1_iobuf: component IOBUF
     port map (
      I => spi_rtl_io1_o,
      IO => spi_rtl_io1_io,
      O => spi_rtl_io1_i,
      T => spi_rtl_io1_t
    );
spi_rtl_sck_iobuf: component IOBUF
     port map (
      I => spi_rtl_sck_o,
      IO => spi_rtl_sck_io,
      O => spi_rtl_sck_i,
      T => spi_rtl_sck_t
    );
spi_rtl_ss_iobuf_0: component IOBUF
     port map (
      I => spi_rtl_ss_o_0(0),
      IO => spi_rtl_ss_io(0),
      O => spi_rtl_ss_i_0(0),
      T => spi_rtl_ss_t
    );
end STRUCTURE;
