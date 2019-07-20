const Postgres = require('pg');

const Pool = Postgres.Pool;
const pool = new Pool({
    user: 'guy',
    host: 'localhost',
    database: 'weather',
    password: 'password'
});

function getChartData_24h(callback) {
    pool.query('SELECT * FROM tph WHERE type = \'AVG\' ORDER BY ts DESC LIMIT 72', (error, results) => {
        if (error) {
            console.log("Error selecting chart data");
            throw error;
        }

        return callback(results.rows);
    });
}

function getChartData_7d(callback) {
    pool.query('SELECT * FROM tph WHERE type = \'AVG\' AND EXTRACT (\'hour\' from ts) IN (0, 6, 12, 18) ORDER BY ts DESC LIMIT 28', (error, results) => {
        if (error) {
            console.log("Error selecting chart data");
            throw error;
        }

        return callback(results.rows);
    });
}

function getChartData_28d(callback) {
    pool.query('SELECT * FROM tph WHERE type = \'AVG\' AND EXTRACT (\'hour\' from ts) = 12 ORDER BY ts DESC LIMIT 28', (error, results) => {
        if (error) {
            console.log("Error selecting chart data");
            throw error;
        }

        return callback(results.rows);
    });
}

function putChartData(ts, type, temperature, pressure, humidity) {
    console.log('Inserting record');

    pool.query('INSERT INTO tph (ts, type, temperature, pressure, humidity) VALUES ($1, $2, $3, $4, $5)', [ts, type, temperature, pressure, humidity], (error, results) => {
        if (error) {
            console.log("Error inserting chart data");
            throw error;
        }
    });
}

module.exports = {
    getChartData_24h,
    getChartData_7d,
    getChartData_28d,
    putChartData
}
