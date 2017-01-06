var current_page = 1; // the page number I'm starting with
var max_page = 3;

function update_page_with_new_items(html) {
    $('#pin-list-head').append(html);
    $('#pin-list-head').masonry();
}

$(window).scroll(function(){
    if($(window).scrollTop() + $(window).height() >= $(document).height() - 500)
    {
       var next = current_page + 1; 
       var data = new Array();
       var lock = null;
       if (next <= max_page && !lock) {
           data.push({name: "page", value: next});
           lock = $.ajax({
                    url: ".",
                    data: data,
                    type: 'GET',
                    success: function(html) {
                        update_page_with_new_items(html);
                        lock = null;
                        current_page++;
                    },
                    error: function(data) {
                        alert('Problem happened.');
                    },
               });
       }
    }
});
