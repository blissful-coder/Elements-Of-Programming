document.addEventListener('DOMContentLoaded', () => {
    const deviceName = 'PB-1012916'; // Replace with your printer's name
    const messageInput = document.getElementById('message');
    const statusText = document.getElementById('status');
    const characteristicsTable = document.getElementById('characteristics');
    const characteristicsSelect = document.getElementById('characteristicsSelect');
    const printButton = document.getElementById('printButton');
    const printResultText = document.getElementById('printResult');
    const printerNameText = document.getElementById('printerName');
    const printerAddressText = document.getElementById('printerAddress');

    // Declare the characteristics array in a higher scope
    let characteristics = [];
    let connectedDevice = null;

    // Replace the service UUID with the one from your printer
    const serviceUUID = '000018f0-0000-1000-8000-00805f9b34fb'; // Replace with your printer's service UUID

    let selectedCharacteristic = null;

    document.getElementById('connectButton').addEventListener('click', async () => {
        try {
            statusText.textContent = 'Connecting...';

            const device = await navigator.bluetooth.requestDevice({
                filters: [{ name: deviceName }],
                optionalServices: [serviceUUID],
            });

            const server = await device.gatt.connect();
            const service = await server.getPrimaryService(serviceUUID);
            const characteristicsIterable = await service.getCharacteristics();

            // Convert the iterable to an array
            characteristics = Array.from(characteristicsIterable);

            // Update connectedDevice with device information
            connectedDevice = device;

            // Display the printer's name and MAC address
            printerNameText.textContent = connectedDevice.name;
            printerAddressText.textContent = connectedDevice.id;

            characteristicsTable.innerHTML = '';

            // Populate the table and the dropdown with descriptions and access properties
            characteristics.forEach((characteristic) => {
                const row = characteristicsTable.insertRow();
                const cell1 = row.insertCell(0);
                const cell2 = row.insertCell(1);

                cell1.textContent = 'Characteristic: ' + getCharacteristicDescription(characteristic.uuid);
                cell2.textContent = `Read: ${characteristic.properties.read}, Write Without Response: ${characteristic.properties.writeWithoutResponse}, Write: ${characteristic.properties.write}, Notify: ${characteristic.properties.notify}, Indicate: ${characteristic.properties.indicate}`;
                
                // Add the characteristic to the dropdown
                const option = document.createElement('option');
                option.value = characteristic.uuid;
                option.text = getCharacteristicDescription(characteristic.uuid);
                characteristicsSelect.appendChild(option);
            });

            characteristicsSelect.disabled = false;
            printButton.disabled = false;
            statusText.textContent = 'Connected';
        } catch (error) {
            console.error('Error:', error);
            statusText.textContent = 'Error: ' + error;
        }
    });

    printButton.addEventListener('click', async () => {
        if (selectedCharacteristic) {
            // Get the multiline receipt data as an array of lines
            const receiptData = [
                'Receipt Title',
                '-----------------------',
                'Item 1: $10.00',
                'Item 2: $15.00',
                'Item 3: $20.00',
                '-----------------------',
                'Total: $45.00',
                'Payment Method: Credit Card',
                '-----------------------',
                'Thank you for your purchase!',
            ];

            // Convert the array of lines to a single string with line breaks
            const message = receiptData.join('\n');

            // Send the formatted multiline receipt data to the selected characteristic
            try {
                await selectedCharacteristic.writeValue(new TextEncoder().encode(message));
                printResultText.textContent = 'Print job sent successfully!';
            } catch (error) {
                console.error('Print Error:', error);
                printResultText.textContent = 'Print job failed: ' + error;
            }
        }
    });


    characteristicsSelect.addEventListener('change', () => {
        selectedCharacteristic = characteristics.find(char => char.uuid === characteristicsSelect.value);
    });

    function getCharacteristicDescription(uuid) {
        return 'Description for ' + uuid;
    }
});
