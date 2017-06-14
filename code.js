$(document).ready(function(){
	$("#1,#2,#3,#4,#5,#6,#7").on("mouseenter",function() {
		// let myName = $(this).attr('name');
		// $("#stadtteilname").text(myName);
    //
		// var value = $(this).attr('id');
		// $("#testme").text(value);
    $.ajax({
      url: 'bezirk_query.php',
      data: "",
      dataType: 'json',
      success: function(rows){
        for (var i in rows)
        {
          var row = rows[i];


          if(row[0] == $(this).attr('name')){
            var id = row[0];
            var districtname = row[1];
            var population = row[2];
            alert(id);
            // $('#stadtteilname').text(row + " " + districtname + " " + population);
          }

        }
      }
    });
	});
	$(".areas").on("mouseleave",function(){
		$("#stadtteilname").text("\xA0");
		$("#testme").text("\xA0");
	});
});
