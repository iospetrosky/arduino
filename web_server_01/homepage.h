const char home_page[] PROGMEM = R"=====(
<html>

<head>
    <meta http-equiv="content-type" content="text/html;charset=UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.4.1/css/bootstrap.min.css">
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.3.1/jquery.min.js"></script>
    <script language=javascript>
        $(document).ready(function () {
            function updateHumidity() {
                $.ajax({
                    url: '/getHumidity', 
                    method: 'GET',
                    success: function (data) {
                        $('#humidity').text(data);
                    },
                    error: function () {
                        $('#humidity').text('Error fetching humidity data');
                    }
                });
            }
            function updateTemperature() {
                $.ajax({
                    url: '/getTemperature', 
                    method: 'GET',
                    success: function (data) {
                        $('#temperature').text(data);
                    },
                    error: function () {
                        $('#temperature').text('Error fetching temperature data');
                    }
                });
            }
            
            // Initial call
            updateHumidity();
            updateTemperature();
            setInterval(updateHumidity, 10000);
            setInterval(updateTemperature, 11000);
        });

    </script>
    <title>Moisture and temperature</title>
</head>

<body>
    <div class="container">
        <h1>Humidity</h1>
        <H2 id="humidity">A</H2>
        <h1>Temperature</h1>
        <h2 id="temperature">B</h2>

    </div>
</body>

</html>
)=====";