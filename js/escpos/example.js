const printer = require("node-bluetooth-escpos-printer");

const macAddress = "20:23:D9:F6:A3:A4"; // Replace with your printer's MAC address

const printData = "Hello, ESC/POS!";

printer
  .init()
  .then(() => printer.connect(macAddress))
  .then(() => printer.print(printData))
  .then(() => printer.close())
  .catch((err) => console.error(err));
