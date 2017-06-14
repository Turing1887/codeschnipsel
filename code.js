$(document).ready(function(){
	$("#1,#2,#3,#4,#5,#6,#7").on("mouseenter",function(e) {
		// let myName = $(this).attr('name');
		// $("#stadtteilname").text(myName);
    //
		// var value = $(this).attr('id');
		// $("#testme").text(value);
    let name = $(this).attr('name');
    $.ajax({
      url: 'bezirk_query.php',
      data: "",
      cache: false,
      async: false,
      dataType: 'json',
      success: function(rows){

        for (var i in rows)
        {
          // var row = rows[i];
          // console.log(rows[0]);
          // var obj = JSON.parse(rows[i]);

          if(rows[i].Stadtteilname == name){

            var id = rows[i].id;
            var districtname = rows[i].Stadtteilname;
            var population = rows[i].Bevölkerung;
            $('#stadtteilname').text(id + " " + districtname + " " + population);
          }

        }
      }
    });
    e.preventDefault();
	});
	$(".areas").on("mouseleave",function(){
		$("#stadtteilname").text("\xA0");
		$("#testme").text("\xA0");
	});
});
