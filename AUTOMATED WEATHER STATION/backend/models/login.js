const { Pool } = require('pg');

const pool = new Pool({
  user: 'postgres',  // Replace with your PostgreSQL username
  host: 'localhost',       // Use 'localhost' or '127.0.0.1' for local connections
  database: 'temperature_humidity_sensor_db',
  password: '',  // Replace with your PostgreSQL password
  port: 5432,              // Default PostgreSQL port
});


const getUsers = () => {
  return new Promise(function(resolve, reject) {
    pool.query('SELECT * FROM users ORDER BY username ASC', (error, results) => {
      if (error) {
        reject(error)
      }
      resolve(results.rows);
    })
  }) 
}

module.exports = {
    getUsers,
}