import EscPosEncoder from "@manhnd/esc-pos-encoder";
import { useState } from "react";

const App = () => {
  const [printers, setPrinters] = useState([]);
  const [selectedPrinter, setSelectedPrinter] = useState(null);

  // Get a list of all thermal Bluetooth printers.
  const getPrinters = async () => {
    const devices = await navigator.bluetooth.getDevices();
    const thermalPrinters = devices.filter((device) => {
      return device.gatt.getPrimaryServices().includes("00001805-0000-1000-8000-00805f9b34fb");
    });
    console.log(thermalPrinters)
    setPrinters(thermalPrinters);
  };

  console.log(getPrinters)
  // Print the bill to the selected printer.
  const printBill = async () => {
    // Connect to the selected thermal Bluetooth printer.
    const printer = await selectedPrinter.gatt.connect();

    // Convert the bill data into ESC/POS commands.
    const escPosCommands = EscPosEncoder.encodeBill({
      // Bill data.
    });

    // Send the ESC/POS commands to the printer.
    await printer.gatt.writePrimaryValue(printer.gatt.getPrimaryService("00001805-0000-1000-8000-00805f9b34fb"), escPosCommands);

    // Disconnect from the printer.
    await printer.gatt.disconnect();
  };

  // Handle the change event of the dropdown menu.
  const handlePrinterChange = (event) => {
    const selectedPrinter = printers.find((printer) => printer.id === event.target.value);
    setSelectedPrinter(selectedPrinter);
  };

  return (
    <div>
      <h1>Print Bill</h1>
      <select value={selectedPrinter?.id} onChange={handlePrinterChange}>
        <option value="">Select a printer</option>
        {printers.map((printer) => (
          <option key={printer.id} value={printer.id}>{printer.name}</option>
        ))}
      </select>
      <button onClick={printBill} disabled={!selectedPrinter}>Print Bill</button>
    </div>
  );
};

export default App;