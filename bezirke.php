
<!DOCTYPE html>
<html lang="de">

  <head>
	<meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <!-- The above 3 meta tags *must* come first in the head; any other head content must come *after* these tags -->
	<meta name"description" content="Districts of Hamburg">
	<meta name"author" content="Florian Wiekhorst, Tien Huy Tonny Van">

	<title>Die Bezirke von Hamburg</title>

	<!-- Bootstrap core CSS -->
    <link href="dist/css/bootstrap.min.css" rel="stylesheet">
		<script src="https://ajax.aspnetcdn.com/ajax/jQuery/jquery-1.12.4.min.js"></script>
	<!-- giev bootstrap icons -->
	<script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/js/bootstrap.min.js"></script>

    <!-- IE10 viewport hack for Surface/desktop Windows 8 bug -->
    <link href="assets/css/ie10-viewport-bug-workaround.css" rel="stylesheet">

    <!-- Custom styles for this template -->
	<link href="cover.css" rel="stylesheet">

	 <!-- HTML5 shim and Respond.js for IE8 support of HTML5 elements and media queries -->
    <!--[if lt IE 9]>
      <script src="https://oss.maxcdn.com/html5shiv/3.7.3/html5shiv.min.js"></script>
      <script src="https://oss.maxcdn.com/respond/1.4.2/respond.min.js"></script>
    <![endif]-->

	<!-- Einbinden der D3-lib -->
	<script src="https://d3js.org/d3.v3.min.js"></script>
    <!-- Einbinden des Bootstrap-Stylesheets -->
    <link rel="stylesheet" href="https://ajax.aspnetcdn.com/ajax/bootstrap/3.3.6/css/bootstrap.min.css">
    <!-- optional: Einbinden der jQuery-Bibliothek -->

    <!-- optional: Einbinden der Bootstrap-JavaScript-Plugins -->
    <script src="https://ajax.aspnetcdn.com/ajax/bootstrap/3.3.6/bootstrap.min.js"></script>
	<link rel="stylesheet" type="text/css" href="CSS/main.css">
  </head>

<body>
<h1>Die Bezirke von Hamburg</h1>
<div id="parent">
		<div id="wide" class="col-sm-8">
		<!-- Button zur Wahl ob Bezirke oder Stadtteile -->
				<div id="bezik_oder_stadtteil">
					<a href="stadtteile.php" class="btn btn-default btn-lg">Stadtteile</a>
				</div>

			<script type="text/javascript">
			//Width and height
            var w = 650;
            var h = 500;

            //Define map projection
            var projection = d3.geo.mercator()
                                   .translate([0, 0])
                                   .scale(1);

            //Define path generator
            var path = d3.geo.path()
                        .projection(projection);

            //Create SVG element

			var svg = d3.select("body")
                        .append("svg")
                        .attr("width", w)
                        .attr("height", h)
						.attr("class", "areas");


            //Load in GeoJSON data
            d3.json("Altona_AL9.GeoJson", function(json) {

                // Calculate bounding box transforms for entire collection
                var b = path.bounds( json ),
                s = 1 / Math.max((b[1][0] - b[0][0]) / w, (b[1][1] - b[0][1]) / h),
                t = [(w - s * (b[1][0] + b[0][0])) / 2, (h - s * (b[1][1] + b[0][1])) / 2];

                // Update the projection
                projection
                  .scale(s)
                  .translate(t);

                //Bind data and create one path per GeoJSON feature
                svg.selectAll("path")
                   .data(json.features)
                   .enter()
				   .append("path")
                   .attr("d", path)
                   .style("fill", "#70bcbf")
				   .attr("class", "bezirke")
				   .attr("id", function(d) { return d.id; })
				   .attr("name", function(d) {return d.name; });
            });
        </script>
			</div>

			<div id="narrow" class="col-sm-4"> <!-- Seitenbereich mit den Angaben -->

					<div id="werte">
						<!-- Überschrift mit StadtteilNamen per Script ändern -->
						<h3 id="stadtteilname">&nbsp;</h3>
						<h3 id="testme">&nbsp;</h3>

				</div>
				<a href="vergleicher.php" class="btn btn-default btn-lg btn-block">Zum Stadtteilvergleicher</a>
			</div>
		</div>

		<!-- Einbinden der code.js -->
		<script src="code.js"></script>
	</body>
</html>
