<script>

$(function() {
var __refresh_options = null;
var current_page = 1;
var max_page_default = 10000;
var max_page = max_page_default;
var qs = "{% format_query_string "page"='XXXX' %}";
var product_top = $('#pin-top').offset().top-25;
    
    function load_pins(retval) {

        retval = $("<div>"+retval+"</div>");
        $(".container").append(retval.find(".pin"));
                
        // show new
        $(".products .product[data-ajax=true]").each(function(i) {
            var prod = this
                                
            setTimeout(function() {
                $(prod).fadeIn("slow");
            }, 400 + i * 100);
        }).removeAttr('data-ajax');
    }
    $(".option input").click(function() {
        
    // clear out previous
   
        clearTimeout(__refresh_options);
        
        __refresh_options = setTimeout(function() {
            // remove the no matching products message if any
            $(".products em").remove();
            
            // reset pages
            current_page = 1;
            max_page = max_page_default;
            
            // remove current products
            $(".product-list .product").remove();
            
            // do first request
            var data = $(".option input").serializeArray()
            data.push({ name: "page", value: 1 });
            $.ajax({
                url: ".",
                data: data,
                success: load_pins
            });
        }, 1100);
    });
    $(".product form").submit(function(e) {
        e.preventDefault();
        
        var form = this;
        
        $.ajax({
            url: "{% url satchmo_cart_add_ajax %}",
            type: "post",
            dataType: "json",
            data: $(this).serializeArray(),
            success: function(retval) {
                $(form).find("button").text("Added")
                    .css({
                        "color": "darkblue",
                        "font-weight": "bold"
                    });
            },
            error: function() {
                $(form).find("button").text("Error")
                    .attr("title", "Please try again later")
                    .css("color", "red");
            }
        });
        
        return false;
    });
    
    // Infinite Scroll
    $(window).scroll(function(){
        if($(window).scrollTop() < product_top){
            $('#scroll-sidebar').fadeOut('slow');
        }
        else{
            $('#scroll-sidebar').fadeIn('slow');
        }

        if($(window).scrollTop() + $(window).height() >= $(document).height() - 600) {
            var next = current_page + 1;
            if(next <= max_page){
                $('#loading-panel').removeClass("hide", "fast");

                var data = $(".option input").serializeArray();
                data.push({name: "page", value: next});
                __refresh_options = $.ajax({
                    url: ".", //qs.replace("XXXX", next),
                    data: data,
                    success: function(html) {
                    // ensure it's not empty
                         if ( ! /\W*<em/.test(html)) {
                       load_pins(html);
                            
                            current_page += 1;
                    } else {
                    max_page = current_page;
                    }
                        $('#loading-panel').addClass("hide", "fast");
                        __refresh_options = null;
                    },
                    error: function() {
                        if(data.error = "undefined"){
                            max_page = current_page-1;
                            $('#loading-panel').addClass("hide", "fast");
                            __refresh_options = null;
                        }
                        else{
                            alert("sorry we had an error")
                        }
                    }
                });
            }
        }
    });
});

</script>
