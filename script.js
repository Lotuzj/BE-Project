// Simulate real-time data updates
function updateDashboard() {
    // Simulate location data
    const latitude = (Math.random() * (90 - (-90)) + (-90)).toFixed(4);
    const longitude = (Math.random() * (180 - (-180)) + (-180)).toFixed(4);
    document.getElementById('latitude').textContent = latitude;
    document.getElementById('longitude').textContent = longitude;

    // Simulate pulse rate (60-100 bpm)
    const pulse = Math.floor(Math.random() * (100 - 60 + 1)) + 60;
    document.getElementById('pulse').textContent = pulse;

    // Simulate gas concentration (0-5 ppm)
    const gas = (Math.random() * 5).toFixed(1);
    document.getElementById('gas').textContent = gas;

    // Update status based on pulse rate
    const status = document.getElementById('status');
    if (pulse > 90) {
        status.textContent = 'Alert';
        status.style.color = '#e74c3c';
    } else {
        status.textContent = 'Active';
        status.style.color = '#27ae60';
    }
}

// Update dashboard every 2 seconds
setInterval(updateDashboard, 2000);

// Initial update
updateDashboard();